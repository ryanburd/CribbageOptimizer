#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using std::string;
using std::vector;
using std::shuffle;

enum Rank {ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
int num_ranks = 13;

enum Suit {spades, clubs, hearts, diamonds};
int num_suits = 4;

// Format a card's rank for printing.
string format_rank(Rank rank)
{
    string rank_string;
    switch(rank)
    {
        case ace:
            rank_string = "A";
            break;
        case two:
            rank_string = "2";
            break;
        case three:
            rank_string = "3";
            break;
        case four:
            rank_string = "4";
            break;
        case five:
            rank_string = "5";
            break;
        case six:
            rank_string = "6";
            break;
        case seven:
            rank_string = "7";
            break;
        case eight:
            rank_string = "8";
            break;
        case nine:
            rank_string = "9";
            break;
        case ten:
            rank_string = "10";
            break;
        case jack:
            rank_string = "J";
            break;
        case queen:
            rank_string = "Q";
            break;
        case king:
            rank_string = "K";
            break;
    };

    return rank_string;
};

// Format a card's suit for printing.
string format_suit(Suit suit)
{
    string suit_string;
    switch(suit)
    {
        case spades:
            suit_string = "S";
            break;
        case clubs:
            suit_string = "C";
            break;
        case hearts:
            suit_string = "H";
            break;
        case diamonds:
            suit_string = "D";
            break;
    };

    return suit_string;
};

struct Card
{
    Rank rank;
    Suit suit;

    // Format a card into a string for printing.
    string format_card()
    {
        string rank_string = format_rank(rank);
        string suit_string = format_suit(suit);

        return rank_string + " " + suit_string;
    };
};

struct Deck
{
    vector<Card> cards;
    int deck_size;

    // Create a standard 52 card deck.
    void build_deck()
    {
        for(int suit = 0; suit < num_suits; suit++)
        {
            for(int rank = 1; rank < num_ranks + 1; rank++)
            {
                Card card;
                card.rank = Rank(rank);
                card.suit = Suit(suit);
                cards.push_back(card);
            };
        };
        deck_size = cards.size();
    };

    // Print the deck.
    void show_deck()
    {
        for(Card card : cards)
        {
            std::cout << card.format_card() << std::endl;
        };
        std::cout << std::endl;
    };

    // Shuffle the deck.
    void shuffle_deck()
    {
        unsigned int seed = time(nullptr);
        shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    };

    // Return only the ranks of the cards in the deck.
    vector<Rank> get_ranks()
    {
        vector<Rank> ranks(deck_size);
        for (int i = 0; i < deck_size; i++)
        {
            ranks[i] = Rank(cards[i].rank);
        };

        return ranks;
    };

    // Deal a hand from the deck passed as a parameter. It is assumed the deck has already been shuffled using shuffle_deck(). Update the number of cards left in the deck after dealing.
    void deal_hand(Deck& house)
    {
        Card top_card;
        for(int i = 0; i < deck_size; i++)
        {
            top_card = house.cards.back();
            cards.push_back(top_card);
            house.cards.pop_back();
        };
        house.deck_size = house.cards.size();
    };
};

enum Dealer {you, opponent};

int choose_dealer();
void identify_dealer(const Dealer&);
void print_ranks(vector<Rank>&);
vector<vector<Rank>> rank_combinations(vector<Rank>&, int&, int&);
void determine_best_hand(Deck&, Dealer&);
void print_best_hand(vector<vector<Rank>>&, int&);
int calculate_rank_points(vector<Rank>&, int&);
int calculate_fifteens(vector<Rank>&, int&);
int calculate_pairs(vector<Rank>&, int&);
int calculate_runs(vector<Rank>&, int&);

int main()
{
    // Print new line for visual purposes.
    std::cout << std::endl;

    // Build the deck of cards. Use show_deck() to view all the cards in the deck.
    Deck house;
    house.build_deck();
    // house.show_deck();

    // Randomly choose the dealer between two players. Use identify_dealer() to print who the dealer is.
    Dealer dealer = Dealer(choose_dealer());
    identify_dealer(dealer);

    // Shuffle the deck.
    house.shuffle_deck();
    // house.show_deck();

    // Deal 6 cards to your hand. Intepretting the end of the vector deck.cards as the top of the deck, use the last 6 cards in deck.cards.
    int cards_per_hand = 6;
    Deck your_hand;
    your_hand.deck_size = cards_per_hand;
    your_hand.deal_hand(house);
    your_hand.show_deck();

    // Determine which 4 cards to keep in your hand and which 2 to place in the crib. To do so, calculate the number of points you'd receive for each permutation of 4 cards from your hand + (-) the points you (opponent) would receive from the 2 remaining cards for the crib. Keep the 4 cards that result in the highest net points, and place the 2 remaining cards in the crib.
    determine_best_hand(your_hand, dealer);

    return 0;
};

// Randomly choose if you or opponent is the dealer.
int choose_dealer()
{
    srand(time(nullptr));
    int dealer = rand() % 2;
    return dealer;
};

// Print who is the dealer.
void identify_dealer(const Dealer& dealer)
{
    switch(dealer)
    {
        case you:
            std::cout << "You are the dealer. You get the crib." << std::endl;
            break;
        case opponent:
            std::cout << "Opponent is the dealer. They get the crib." << std::endl;
            break;
    };
    std::cout << std::endl;
};

// Print a card's rank.
void print_ranks(vector<Rank>& ranks)
{
    string rank_string;

    for (Rank rank : ranks)
    {
        rank_string = format_rank(rank);
        std::cout << rank_string << ", ";
    };

    std::cout << std::endl;
};

// Return all possible combinations of ranks with the combo size passed from the passed vector of ranks.
vector<vector<Rank>> rank_combinations(vector<Rank>& ranks, int& numRanks, int& ranksPerCombo)
{
    vector<Rank> combo;
    vector<vector<Rank>> rank_combos;

    for (int rank1 = 0; rank1 < numRanks; rank1++)
    {
        // Add rank1 to the current combo.
        combo.push_back(ranks[rank1]);
        for (int rank2 = rank1 + 1; rank2 < numRanks; rank2++)
        {
            // Add rank2 to the current combo.
            combo.push_back(ranks[rank2]);
            // If we need a combo of 3 ranks, loop over rank3.
            if (ranksPerCombo > 2)
            {
                for (int rank3 = rank2 + 1; rank3 < numRanks; rank3++)
                {
                    // Add rank3, finishing the current combo. Add the combo to the vector of combos and remove rank3 to get the next combo.
                    combo.push_back(ranks[rank3]);
                    rank_combos.push_back(combo);
                    combo.pop_back();
                };
                // When done looping over the rank3's, remove the current rank2 to get the next combo.
                combo.pop_back();
            }
            else
            {
                // If we only need combos of 2 ranks, the combo is finished. Add it to the vector of combos and remove rank2 to get the next combo.
                rank_combos.push_back(combo);
                combo.pop_back();
            };
        };
        // Remove rank1 to get the next combo.
        combo.pop_back();
    };

    // Return the vector containing all the possible rank combos.
    return rank_combos;
};

void determine_best_hand(Deck& deck, Dealer& dealer)
{
    // First, calculate the points awarded from the ranks.
    
    // Get a vector of the ranks for simpler coding of the point calculations.
    vector<Rank> ranks = deck.get_ranks();

    int numHandRanks = 4;
    int numCribRanks = deck.deck_size - numHandRanks;

    // Get all the unique 2 card combinations that can be placed in the crib. For each unique combo, the remaining 4 cards will be kept in the hand. Looping over 2 card combos for the crib makes the code within card_combinations shorter compared to having to loop over 4 cards to keep in the hand.
    vector<vector<Rank>> crib_combos = rank_combinations(ranks, deck.deck_size, numCribRanks);

    // Copy all the ranks into the hand ranks. The crib ranks will be removed from the hand ranks without changing the total vector of ranks.
    vector<Rank> hand_ranks = ranks;

    int handPoints, cribPoints, netPoints, maxPoints = 0;
    vector<vector<Rank>> best_hands, best_cribs;

    for (vector<Rank> crib_ranks : crib_combos)
    {
        // Remove the crib ranks from the hand ranks.
        auto rank1_index = find(hand_ranks.begin(), hand_ranks.end(), crib_ranks[0]);
        hand_ranks.erase(hand_ranks.begin() + std::distance(hand_ranks.begin(), rank1_index));
        auto rank2_index = find(hand_ranks.begin(), hand_ranks.end(), crib_ranks[1]);
        hand_ranks.erase(hand_ranks.begin() + std::distance(hand_ranks.begin(), rank2_index));

        // Calculate points from the ranks kept in the hand.
        handPoints = calculate_rank_points(hand_ranks, numHandRanks);

        // If there are 3 or more players in the game, each player only places 1 card in the crib, so no points can be awarded from the 1 card alone.
        if (numCribRanks == 1)
        {
            cribPoints = 0;
        }
        // Calculate points from the ranks placed in the crib.
        else
        {
            cribPoints = calculate_rank_points(crib_ranks, numCribRanks);
        };

        // Add (subtract) crib points to hand points if you (opponent) are the dealer.
        if (dealer == you)
        {
            netPoints = handPoints + cribPoints;
        }
        else if (dealer == opponent)
        {
            netPoints = handPoints - cribPoints;
        };

        // If the net points from the current hand/crib are greater than the current maximum net points, set the maximum to the current net points, clear the best hands and best cribs, and assign the current hand ranks and crib ranks as the best hand and crib, respectively.
        if (netPoints > maxPoints)
        {
            maxPoints = netPoints;
            best_hands.clear();
            best_hands.push_back(hand_ranks);
            best_cribs.clear();
            best_cribs.push_back(crib_ranks);
        }
        // If the net points from the current hand/crib are equal to the current maximum net points, add the hand ranks and crib ranks to the vector of best hands and cribs, respectively. All hands and cribs within these vectors will result in the same total net points. Further analysis is needed to determine which of these hands/cribs the player should play.
        else if (netPoints == maxPoints)
        {
            best_hands.push_back(hand_ranks);
            best_cribs.push_back(crib_ranks);
        };

        // Reset the hand ranks to all the ranks so the next combo of crib ranks can be removed in the next loop iteration.
        hand_ranks = ranks;
    };
    print_best_hand(best_hands, maxPoints);
};

void print_best_hand(vector<vector<Rank>>& best_hands, int& maxPoints)
{
    std::cout << "Maximum points = " << maxPoints << std::endl;
    if (maxPoints == 0)
    {
        std::cout << "No points possible." << std::endl;
    }
    else
    {
        std::cout << "Cards to keep in your hand:" << std::endl;
        for (vector<Rank> hand : best_hands)
        {
            print_ranks(hand);
        };
        std::cout << std::endl;
    };
};

int calculate_rank_points(vector<Rank>& ranks, int& numRanks)
{
    int fifteensPoints = calculate_fifteens(ranks, numRanks);
    int pairsPoints = calculate_pairs(ranks, numRanks);
    int runsPoints = calculate_runs(ranks, numRanks);

    int total_points = fifteensPoints + pairsPoints + runsPoints;

    return total_points;
};

int calculate_fifteens(vector<Rank>& original_ranks, int& numRanks)
{
    int numFifteens = 0;
    int pointsPerFifteen = 2;

    // Create a copy of the ranks vector in case numerical values need to be temporarily changed (see next step).
    vector<Rank> ranks = original_ranks;

    // All face cards count as 10 for calculating 15s. If any ranks are a jack, queen, or king, change their numerical value to 10.
    for (int i = 0; i < numRanks; i++)
    {
        if (ranks[i] > 10)
        {
            ranks[i] = Rank(10);
        };
    };

    // For a crib of 2 ranks, add the two ranks to check if they sum to 15. If so, increment numFifteens to 1.
    if (numRanks == 2)
    {
        if (ranks[0] + ranks[1] == 15)
        {
            numFifteens++;
        };
    }
    // For a hand (4 ranks), determine all the possible 2, 3, and 4 rank combinations. Check if each combo sums to 15. Increment numFifteens by 1 for each combo summing to 15.
    else
    {
        int numRanks = 4;
        int comboSum = 0;
        for (int ranksPerCombo = 2; ranksPerCombo < numRanks + 1; ranksPerCombo++)
        {
            // Get all possible combos of the ranks.
            vector<vector<Rank>> rank_combos;
            if (ranksPerCombo == 4)
            {
                rank_combos = {ranks};
            }
            else
            {
                rank_combos = rank_combinations(ranks, numRanks, ranksPerCombo);
            };

            // Calculate the sum of the ranks for each combo. Increment numFifteens if the sum = 15.
            for (vector<Rank> combo : rank_combos)
            {
                for (Rank rank : combo)
                {
                    comboSum += rank;
                };
                if (comboSum == 15)
                {
                    numFifteens++;
                };

                // Reset the sum to 0 for the next combo to be summed.
                comboSum = 0;
            };
        };
    };

    return numFifteens*pointsPerFifteen;
};

int calculate_pairs(vector<Rank>& ranks, int& numRanks)
{
    int numPairs = 0;
    int pointsPerPair = 2;

    return numPairs*pointsPerPair;
};

int calculate_runs(vector<Rank>& ranks, int& numRanks)
{
    int numRuns = 0;
    int pointsPerRun; // Equals the size of the run.

    return numRuns*pointsPerRun;
};