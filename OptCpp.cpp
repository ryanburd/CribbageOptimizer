#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::string;
using std::vector;

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
    int size;
};

void build_deck(Deck&);
string format_card(const Card&);
void print_deck(const Deck&);

int main()
{
    // Build the deck of cards.
    Deck house;
    build_deck(house);
    print_deck(house);

    /* Randomly choose the dealer between two players:
    *  0 for self, 1 for opponent
    */
    // srand(time(nullptr));
    // short dealer = rand() % 2;
    // std::cout << dealer;

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
    deck.size = sizeof(deck.cards);
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

void print_deck(const Deck& deck)
{
    for(Card card : deck.cards)
        std::cout << format_card(card) << std::endl;
};