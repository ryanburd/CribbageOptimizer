#include <iostream>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    /* Build the deck of cards.
    *  Face cards will be assigned a number for ease of calculating points from
    *  runs: Jack = 11, Queen = 12, King = 13
    */
    string suits[4] = {"S", "C", "H", "D"};
    int values[13];
    iota(values, values + 13, 1);
    for (auto i : values)
        cout << i << endl;

    /* Randomly choose the dealer between two players:
    *  0 for self, 1 for opponent
    */
    srand(time(nullptr));
    short dealer = rand() % 2;
    cout << dealer;

    return 0;
}