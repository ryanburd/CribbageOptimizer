# Cribbage Optimizer

This repository contains an optimizer that determines the best cards for a user to keep in their hand and discard into the crib.

## Current status (C++ version)
1) Deck of cards is created.
2) Dealer randomly determined to determine which player receives the crib.
3) 6 cards dealt to your hand.
4) Function written to calculate card combinations of a specified size. This function will be used in future updates to determine all possible 4 card combinations you can keep in your hand and which hand will result in the highest net total points.

## Current status (Python version)
1) Deck of cards generated
2) 6 random cards dealt into 1 hand
3) Randomly determine the dealer to determine which player receives the crib
4) All permutations of 4 cards have their total points calculated from 15s, pairs, and runs
5) The 4 card hand(s) that yield the maximum number of points is saved and printed