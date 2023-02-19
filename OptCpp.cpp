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

enum Dealer {you, opponent};

void build_deck(Deck&);
string format_card(const Card&);
void show_deck(const Deck&);
int choose_dealer();
void identify_dealer(const Dealer&);

int main()
{
    // Build the deck of cards. Use show_deck to view all the cards in the deck.
    Deck house;
    build_deck(house);
    // show_deck(house);

    // Randomly choose the dealer between two players. Use identify_dealer to print who the dealer is.
    Dealer dealer = Dealer(choose_dealer());
    identify_dealer(dealer);

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

void show_deck(const Deck& deck)
{
    for(Card card : deck.cards)
        std::cout << format_card(card) << std::endl;
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