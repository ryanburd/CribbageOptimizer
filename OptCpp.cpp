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
vector<Deck> card_combinations(Deck&, int&);
// void determine_best_hand(Deck&, Dealer&);
// int calculate_points(const Deck&);
// int calculate_fifteens(Deck&);
// int calculate_pairs(Deck&);
// int calculate_runs(Deck&);

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
    // determine_best_hand(your_hand, dealer);

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
            rank_string = "Ace";
            break;
        case two:
            rank_string = "Two";
            break;
        case three:
            rank_string = "Three";
            break;
        case four:
            rank_string = "Four";
            break;
        case five:
            rank_string = "Five";
            break;
        case six:
            rank_string = "Six";
            break;
        case seven:
            rank_string = "Seven";
            break;
        case eight:
            rank_string = "Eight";
            break;
        case nine:
            rank_string = "Nine";
            break;
        case ten:
            rank_string = "Ten";
            break;
        case jack:
            rank_string = "Jack";
            break;
        case queen:
            rank_string = "Queen";
            break;
        case king:
            rank_string = "King";
            break;
    };

    string suit_string;
    switch(card.suit)
    {
        case spades:
            suit_string = "Spades";
            break;
        case clubs:
            suit_string = "Clubs";
            break;
        case hearts:
            suit_string = "Hearts";
            break;
        case diamonds:
            suit_string = "Diamonds";
            break;
    };

    return rank_string + " of " + suit_string;
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

vector<Deck> card_combinations(Deck& deck, int& cardsPerCombo)
{
    Deck combo;
    vector<Deck> card_combos;

    // We only ever need to calculate combinations of exactly 2 or 3 cards. The first two for loops loop over the possible combinations of 2 cards. An if statement allows another for loop for 3 card combinations if necessary.
    for (int card1 = 0; card1 < deck.deck_size; card1++)
    {
        // Add a first card to the combo.
        combo.cards.push_back(deck.cards[card1]);

        // Only loop over the second cards if the first card is not already at the end of the deck passed to the function.
        if (card1 < deck.deck_size - 1)
        {
            for (int card2 = card1 + 1; card2 < deck.deck_size; card2++)
            {
                // Add a second card to the combo.
                combo.cards.push_back(deck.cards[card2]);
                // If we need a combo of size 3, loop over the remaining cards as the third card.
                if (cardsPerCombo > 2)
                {
                    // Only loop over the third cards if the second card is not already at the end of the deck passed to the function.
                    if (card2 < deck.deck_size - 1)
                    {
                        for (int card3 = card2 + 1; card3 < deck.deck_size; card3++)
                        {
                            // Add a third card. With the combo complete, add the combo to the vector containing all possible combos. Then remove the third card to get the next possible third card on the next loop iteration.
                            combo.cards.push_back(deck.cards[card3]);
                            card_combos.push_back(combo);
                            combo.cards.pop_back();
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
                    card_combos.push_back(combo);
                };
                // Remove the second card (third card, if applicable, is already removed) to get the next possible second card on the next loop iteration.
                combo.cards.pop_back();
            };
            // Remove the first card (second and third, if applicable, cards are already removed) to get the next possible first card on the next loop iteration.
            combo.cards.pop_back();
        }
        // If the first card is at the end of the deck passed to the function, then there are no more combos left. Break here ends the card1 for loop.
        else
        {
            break;
        };
    };

    return card_combos;
};

// void determine_best_hand(Deck& hand, Dealer& dealer)
// {
//     Deck hand_cards, crib_cards;
//     int numHandCards = 4;
//     hand_cards.deck_size = numHandCards;
//     crib_cards.deck_size = hand.deck_size - numHandCards;

//     int hand_points, crib_points, net_points, max_points;
//     vector<Deck> best_hands, best_cribs;

//     do
//     {
//         // Keep the first 4 cards of the permutation in the hand.
//         for(int i = 0; i < numHandCards; i++)
//         {
//             hand_cards.cards.push_back(hand.cards[i]);
//         };
//         // Put the remaining cards of the permutation in the crib.
//         for(int i = numHandCards; i < hand.deck_size; i++)
//         {
//             crib_cards.cards.push_back(hand.cards[i]);
//         };

//         hand_points = calculate_points(hand_cards);

//         // If there are 3 or more players in the game, each player only places 1 card in the crib, so no points can be awarded from the 1 card alone.
//         if (crib_cards.deck_size == 1)
//         {
//             crib_points = 0;
//         }
//         else
//         {
//             crib_points = calculate_points(crib_cards);
//         };

//         if (dealer == you)
//         {
//             net_points = hand_points + crib_points;
//         }
//         else if (dealer == opponent)
//         {
//             net_points = hand_points - crib_points;
//         };

//         // If the net points from the current permutation are greater than the current maximum net points, set the maximum to the current net points, clear the best hands and best cribs, and assign the current hand cards and crib cards as the best hand and crib, respectively.
//         if (net_points > max_points)
//         {
//             max_points = net_points;
//             best_hands.clear();
//             best_hands.push_back(hand_cards);
//             best_cribs.clear();
//             best_cribs.push_back(crib_cards);
//         }
//         // If the net points from the current permutation are equal to the current maximum net points, add the hand cards and crib cards to the vector of best hands and cribs, respectively. All hands and cribs within these vectors will result in the same total net points. Further analysis is needed to determine which of these hands/cribs the player should play.
//         else if (net_points == max_points)
//         {
//             best_hands.push_back(hand_cards);
//             best_cribs.push_back(crib_cards);
//         };
//     } while (std::next_permutation(hand.cards.begin(), hand.cards.end()));
    
// };

// int calculate_points(const Deck& deck)
// {
//     int fifteensPoints = calculate_fifteens(deck);
//     int pairsPoints = calculate_pairs(deck);
//     int runsPoints = calculate_runs(deck);

//     int total_points = fifteensPoints + pairsPoints + runsPoints;

//     return total_points;
// };

// int calculate_fifteens(Deck& deck)
// {
//     int numFifteens;

//     // For a crib of 2 cards, add the two cards to check if they sum to 15. If so, increment numFifteens to 1.
//     if (deck.deck_size == 2)
//     {
//         if (deck.cards[0].rank + deck.cards[1].rank = 15)
//         {
//             numFifteens++;
//         };
//     }
//     else
//     {
//         do
//         {

//         } while (std::next_permutation(deck.cards.begin(), deck.cards.end()));
//     };
// };