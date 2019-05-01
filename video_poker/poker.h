/**
 * This program was adapted from Paul Wilkinson's CS045 lectures.
 */

#ifndef CS045_POKER_H
#define CS045_POKER_H

#include <iostream>
#include <ncurses.h>

namespace poker{

    struct playerHand {
        unsigned int faceValue[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0},
                suitValue[4] = {0,0,0,0},
                pairs = 0;

        bool royalStraightFlush = false;
        bool hasAceKing = false;
        bool fourOfAKind = false;
        bool threeOfAKind = false;
        bool straight = false;
        bool flush = false;
        bool fullHouse = false;

    };

    void main();
    void loadCardValueAndSuits(std::string faceValue[], std::string suitValue[]);
    void shuffleDeck(bool deck[]);
    bool again(std::string title);
    void dealAHand(bool deck[], unsigned int hand[5]);
    void displayHand(unsigned int hand[5], std::string suitValue[], std::string faceValue[]);
    void scoreHand(unsigned int hand[5]);
    void checkForHand(playerHand * my);
    void scoreHand(unsigned int hand[5]);
    void initGame();
    void exitGame();
    void displayMainWindow();


}

#endif //CS045_POKER_H
