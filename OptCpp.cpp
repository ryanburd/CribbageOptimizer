#include <iostream>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <ctime>

// using namespace std;

int main() {
    /* Build the deck of cards.
    *  Face cards will be assigned a number for ease of calculating points from
    *  runs: Jack = 11, Queen = 12, King = 13
    */
    struct card {
        enum class CardSuit : unsigned char {
            spades,
            clubs,
            hearts,
            diamonds
        };
        enum class CardValue : unsigned char {
            ace = 1,
            two,
            three,
            four,
            five,
            six,
            seven,
            eight,
            nine,
            ten,
            jack,
            queen,
            king
        };
        CardSuit suit;
        CardValue value;
    };
    card AceSpade;
    AceSpade.suit = card::CardSuit::spades;
    AceSpade.value = card::CardValue::ace;

    /* Randomly choose the dealer between two players:
    *  0 for self, 1 for opponent
    */
    srand(time(nullptr));
    short dealer = rand() % 2;
    std::cout << dealer;

    return 0;
}