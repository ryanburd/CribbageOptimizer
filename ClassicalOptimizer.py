import numpy as np
import random
import itertools

# Build the deck of cards
suits = 'S C H D'.split()
values = ['']*13
values[0],values[10],values[11],values[12] = 'A','J','Q','K'
values[1:10] = range(2,11)
deck = [list(tup) for tup in itertools.product(values,suits)]

# Generate a random hand of 6 cards
hand = random.sample(deck,k=6)
hand_values = list(range(4))
for i in range(4):
    hand_values[i] = hand[i][0]

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

points = fifteens(hand_values) + pairs(hand_values)

print(hand)
print(hand_values)
print(points)