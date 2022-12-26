import numpy as np
import random
import itertools

# Build the deck of cards
suits = 'S C H D'.split()
values = ['']*13
values[0],values[10],values[11],values[12] = 'A','J','Q','K'
values[1:10] = range(2,11)
deck = [list(tup) for tup in itertools.product(values,suits)]

# Calculate the points from combinations of 15
def fifteens(self):
    numbers = np.zeros(4)
    for i in range(4):
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
    for i in range(6):
        if combos[i][0] == combos[i][1]: num_pairs+=1
    return num_pairs*2

def runs(self):
    numbers = np.zeros(4)
    for i in range(4):
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
    diff_numbers = [uniq[i+1]-uniq[i] for i in range(len(uniq)-1)]
    run_size = 3
    num_runs = 0
    if len(uniq) >= 3:
        for i in range(len(diff_numbers)-1):
            if all(diff_numbers==1):
                run_size = len(uniq)
                if (len(dupes) == 2) & (dupes[0] != dupes[-1]): num_runs = 4
                else: num_runs = 1+len(dupes)
            
            # Stil working on code starting here
            elif (diff_numbers[i] == 1) & (diff_numbers[i+1] == 1):
                num_runs = 1
    return run_size*num_runs

# Generate a random hand of 6 cards
hand = random.sample(deck,k=6)
hand_values = list(range(6))
for i in range(6):
    hand_values[i] = hand[i][0]
hand_values = [2,3,3,4,7,7]
# Calculate the highest point total possible using any 4 cards in the hand
max_hand = []
max_points = 0
for tup in itertools.combinations(hand_values,r=4):
    points = fifteens(tup) + pairs(tup) + runs(tup)
    if points > max_points:
        max_points = points
        max_hand = [list(tup)]
    elif points == max_points: max_hand.append(list(tup))

print(hand)
print(hand_values)
print(max_hand)
print(max_points)