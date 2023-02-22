#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using std::string;
using std::vector;
using std::shuffle;

enum Rank {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
int num_ranks = 13;

enum Suit {spades, clubs, hearts, diamonds};
int num_suits = 4;

struct Card
{
    Rank rank;
    Suit suit;
};

struct Deck
{
    vector<Card> cards;
    int deck_size;
};

enum Dealer {you, opponent};

void build_deck(Deck&);
string format_card(const Card&);
void show_deck(const Deck&);
int choose_dealer();
void identify_dealer(const Dealer&);
void shuffle_deck(Deck&);
void deal_hand(Deck&, Deck&);
vector<Rank> get_ranks(const Deck& deck);
vector<Deck> card_combinations(Deck&, int&);
void determine_best_hand(Deck&, Dealer&);
int calculate_rank_points(vector<Rank>&, int&);
int calculate_fifteens(vector<Rank>&, int&);
int calculate_pairs(vector<Rank>&, int&);
int calculate_runs(vector<Rank>&, int&);

int main()
{
    // Print new line for visual purposes.
    std::cout << std::endl;

    // Build the deck of cards. Use show_deck to view all the cards in the deck.
    Deck house;
    build_deck(house);
    // show_deck(house);

    // Randomly choose the dealer between two players. Use identify_dealer to print who the dealer is.
    Dealer dealer = Dealer(choose_dealer());
    identify_dealer(dealer);

    // Shuffle the deck.
    shuffle_deck(house);
    // show_deck(house);

    // Deal 6 cards to your hand. Intepretting the end of the vector deck.cards as the top of the deck, use the last 6 cards in deck.cards.
    int cards_per_hand = 6;
    Deck your_hand;
    your_hand.deck_size = cards_per_hand;
    deal_hand(house, your_hand);
    show_deck(your_hand);

    // Determine which 4 cards to keep in your hand and which 2 to place in the crib. To do so, calculate the number of points you'd receive for each permutation of 4 cards from your hand + (-) the points you (opponent) would receive from the 2 remaining cards for the crib. Keep the 4 cards that result in the highest net points, and place the 2 remaining cards in the crib.
    determine_best_hand(your_hand, dealer);

    return 0;
};

void build_deck(Deck& deck)
{
    for(int suit = 0; suit < num_suits; suit++)
    {
        for(int rank = 0; rank < num_ranks; rank++)
        {
            Card card;
            card.rank = Rank(rank);
            card.suit = Suit(suit);
            deck.cards.push_back(card);
        };
    };
    deck.deck_size = deck.cards.size();
};

string format_card(const Card& card)
{
    string rank_string;
    switch(card.rank)
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

    string suit_string;
    switch(card.suit)
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

    return rank_string + " " + suit_string;
};

void show_deck(const Deck& deck)
{
    for(Card card : deck.cards)
    {
        std::cout << format_card(card) << std::endl;
    };
    std::cout << std::endl;
};

int choose_dealer()
{
    srand(time(nullptr));
    int dealer = rand() % 2;
    return dealer;
};

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

void shuffle_deck(Deck& deck)
{
    unsigned int seed = time(nullptr);
    shuffle(deck.cards.begin(), deck.cards.end(), std::default_random_engine(seed));
};

void deal_hand(Deck& house, Deck& hand)
{
    Card top_card;
    for(int i = 0; i < hand.deck_size; i++)
    {
        top_card = house.cards.back();
        hand.cards.push_back(top_card);
        house.cards.pop_back();
    };
    house.deck_size = house.cards.size();
};

vector<Rank> get_ranks(const Deck& deck)
{
    vector<Rank> ranks;
    for (int i = 0; i < deck.deck_size; i++)
    {
        ranks[i] = deck.cards[i].rank;
    };

    return ranks;
};

vector<vector<Rank>> rank_combinations(vector<Rank>& ranks, int& numRanks, int& ranksPerCombo)
{
    vector<Rank> combo;
    vector<vector<Rank>> rank_combos;

    // We only ever need to calculate combinations of exactly 2 or 3 cards. The first two for loops loop over the possible combinations of 2 cards. An if statement allows another for loop for 3 card combinations if necessary.
    for (int rank1 = 0; rank1 < numRanks; rank1++)
    {
        // Add a first card to the combo.
        combo.push_back(ranks[rank1]);

        // Only loop over the second cards if the first card is not already at the end of the deck passed to the function.
        if (rank1 < numRanks - 1)
        {
            for (int rank2 = rank1 + 1; rank2 < numRanks; rank2++)
            {
                // Add a second card to the combo.
                combo.push_back(ranks[rank2]);
                // If we need a combo of size 3, loop over the remaining cards as the third card.
                if (ranksPerCombo > 2)
                {
                    // Only loop over the third cards if the second card is not already at the end of the deck passed to the function.
                    if (rank2 < numRanks - 1)
                    {
                        for (int rank3 = rank2 + 1; rank3 < numRanks; rank3++)
                        {
                            // Add a third card. With the combo complete, add the combo to the vector containing all possible combos. Then remove the third card to get the next possible third card on the next loop iteration.
                            combo.push_back(ranks[rank3]);
                            rank_combos.push_back(combo);
                            combo.pop_back();
                        };
                    }
                    // If the second card is already at the end of the deck passed to the function, there are no more possible combos of size 3 using the current first card. Break here ends the card2 for loop and goes to the next iteration of the first card.
                    else
                    {
                        break;
                    };
                }
                // If we need a combo of size 2, the combo is complete, so add it to the vector containing all possible combos.
                else
                {
                    rank_combos.push_back(combo);
                };
                // Remove the second card (third card, if applicable, is already removed) to get the next possible second card on the next loop iteration.
                combo.pop_back();
            };
            // Remove the first card (second and third, if applicable, cards are already removed) to get the next possible first card on the next loop iteration.
            combo.pop_back();
        }
        // If the first card is at the end of the deck passed to the function, then there are no more combos left. Break here ends the card1 for loop.
        else
        {
            break;
        };
    };

    return rank_combos;
};

void determine_best_hand(Deck& deck, Dealer& dealer)
{
    // First, calculate the points awarded from the ranks. Get a vector of the ranks for simpler coding of the point calculations.
    vector<Rank> ranks = get_ranks(deck);

    int numHandRanks = 4;
    int numCribRanks = deck.deck_size - numHandRanks;

    // Get all the unique 2 card combinations that can be placed in the crib. For each unique combo, the remaining 4 cards will be kept in the hand. Looping over 2 card combos for the crib makes the code within card_combinations shorter compared to having to loop over 4 cards to keep in the hand.
    vector<vector<Rank>> crib_combos = rank_combinations(ranks, deck.deck_size, numCribRanks);

    // Copy all the ranks into the hand ranks. The crib ranks will be removed from the hand ranks without changing the total vector of ranks.
    vector<Rank> hand_ranks = ranks;

    for (vector<Rank> crib_ranks : crib_combos)
    {
        // Remove the crib ranks from the hand ranks.
        auto rank1_index = find(hand_ranks.begin(), hand_ranks.end(), crib_ranks[0]);
        hand_ranks.erase(hand_ranks.begin() + std::distance(hand_ranks.begin(), rank1_index));
        auto rank2_index = find(hand_ranks.begin(), hand_ranks.end(), crib_ranks[1]);
        hand_ranks.erase(hand_ranks.begin() + std::distance(hand_ranks.begin(), rank2_index));

        int handPoints = calculate_rank_points(hand_ranks, numHandRanks);

        int cribPoints, netPoints;

        // If there are 3 or more players in the game, each player only places 1 card in the crib, so no points can be awarded from the 1 card alone.

        if (numCribRanks == 1)
        {
            cribPoints = 0;
        }
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

        // If the net points from the current permutation are greater than the current maximum net points, set the maximum to the current net points, clear the best hands and best cribs, and assign the current hand cards and crib cards as the best hand and crib, respectively.
        int maxPoints;
        vector<vector<Rank>> best_hands, best_cribs;

        if (netPoints > maxPoints)
        {
            maxPoints = netPoints;
            best_hands.clear();
            best_hands.push_back(hand_ranks);
            best_cribs.clear();
            best_cribs.push_back(crib_ranks);
        }
        // If the net points from the current permutation are equal to the current maximum net points, add the hand cards and crib cards to the vector of best hands and cribs, respectively. All hands and cribs within these vectors will result in the same total net points. Further analysis is needed to determine which of these hands/cribs the player should play.
        else if (netPoints == maxPoints)
        {
            best_hands.push_back(hand_ranks);
            best_cribs.push_back(crib_ranks);
        };

        // Reset the hand ranks to all the ranks so the next combo of crib ranks can be removed in the next loop iteration.
        hand_ranks = ranks;
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

int calculate_fifteens(vector<Rank>& ranks, int& numRanks)
{
    int numFifteens;
    int pointsPerFifteen = 2;

    // For a crib of 2 ranks, add the two ranks to check if they sum to 15. If so, increment numFifteens to 1.
    if (numRanks == 2)
    {
        if (ranks[0] + ranks[1] == 15)
        {
            numFifteens++;
        };
    }
    else
    {
        
    };

    return numFifteens*pointsPerFifteen;
};

int calculate_pairs(vector<Rank>& ranks, int& numRanks)
{
    int numPairs;
    int pointsPerPair = 2;

    return numPairs*pointsPerPair;
};

int calculate_runs(vector<Rank>& ranks, int& numRanks)
{
    int numRuns;
    int pointsPerRun; // Equals the size of the run.

    return numRuns*pointsPerRun;
};