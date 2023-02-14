import numpy as np
import random
import itertools
from collections import Counter

# Calculate the points from combinations of 15
def fifteens(self):
    numbers = np.zeros(len(self))
    for i in range(len(self)):
        if isinstance(self[i],str):
            if self[i] == 'A': numbers[i] = 1
            else: numbers[i] = 10
        else:
            numbers[i] = self[i]
    two_cards = np.array([sum(tup) for tup in itertools.combinations(numbers,r=2)])
    three_cards = np.array([sum(tup) for tup in itertools.combinations(numbers,r=3)])
    four_cards = np.array([sum(tup) for tup in itertools.combinations(numbers,r=4)])
    num_fifteens = len(two_cards[two_cards==15])+len(three_cards[three_cards==15])+len(four_cards[four_cards==15])
    return num_fifteens*2

# Calculate the points from pairs
def pairs(self):
    combos = [tup for tup in itertools.combinations(self,r=2)]
    num_pairs = 0
    for i in range(len(combos)):
        if combos[i][0] == combos[i][1]: num_pairs+=1
    return num_pairs*2

# Calculate the points from runs
def runs(self):
    numbers = np.zeros(len(self))
    for i in range(len(self)):
        if isinstance(self[i],str):
            if self[i] == 'A': numbers[i] = 1
            elif self[i] == 'J': numbers[i] = 11
            elif self[i] == 'Q': numbers[i] = 12
            elif self[i] == 'K': numbers[i] = 13
        else: numbers[i] = self[i]
    numbers = sorted(numbers)
    uniq = []
    dupes = []
    for i in numbers:
        if i in uniq: dupes.append(i)
        else: uniq.append(i)
    if len(uniq) >= 3: diff_numbers = [uniq[i+1]-uniq[i] for i in range(len(uniq)-1)]
    else: uniq = []
    while len(uniq) >= 3:
        if all(diff_numbers[i] == 1 for i in range(len(diff_numbers))): break
        elif len(uniq) == 3:
            uniq = []
            break
        else:
            for i in range(len(diff_numbers)):
                if diff_numbers[i] > 1:
                    if i < 2:
                        uniq, diff_numbers = uniq[i+1:], diff_numbers[i+1:]
                    else:
                        uniq, diff_numbers = uniq[:i+1], diff_numbers[:i]
                    break
    run_size = len(uniq)
    if run_size >= 3:
        for dupe in dupes:
            if dupe in uniq: continue
            else: dupes.remove(dupe)
        if len(dupes) == 2:
            if dupes[0] != dupes[1]: num_runs = 4
            else: num_runs = 3
        else: num_runs = 1+len(dupes)
    else: num_runs = 0
    return run_size*num_runs

def main():
    # Build the deck of cards
    suits = 'S C H D'.split()
    values = ['']*13
    values[0],values[10],values[11],values[12] = 'A','J','Q','K'
    values[1:10] = range(2,11)
    deck = [list(tup) for tup in itertools.product(values,suits)]

    # Generate a random hand of 6 cards
    dealer = random.getrandbits(1)
    hand = random.sample(deck,k=6)
    hand_values = list(range(6))
    for i in range(6):
        hand_values[i] = hand[i][0]

    # Calculate the highest point total possible using any 4 cards in the hand
    max_hand = []
    max_net_points = 0
    to_crib = []
    for tup in itertools.combinations(hand_values,r=4):
        hand_points = fifteens(tup) + pairs(tup) + runs(tup)
        # Line below will remove all duplicates of a card value; FIX THIS
        discard = set(hand_values) - set(tup)
        print(hand_values)
        print(discard)
        crib_points = fifteens(discard) + pairs(discard) + runs(discard)
        if not dealer: crib_points = -1*crib_points
        net_points = hand_points+crib_points
        if net_points > max_net_points:
            max_net_points = net_points
            max_hand = [list(tup)]
            to_crib = [discard]
        elif net_points == max_net_points:
            max_hand.append(list(tup))
            to_crib.append(discard)

    if dealer: print('Your crib')
    else: print("Opponent's crib")
    print(hand)
    print('Hand =',hand_values)
    print('Best hand =',max_hand)
    print('For crib =',to_crib)
    print('Net points =',max_net_points)

if __name__ == "__main__":
    main()
