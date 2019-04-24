/**
 * This program was adapted from Paul Wilkinson's CS045 lectures.
 */

#ifndef CS045_POKER_H
#define CS045_POKER_H

#include <iostream>

namespace poker{
    void main();
    void loadCardValueAndSuits(std::string faceValue[], std::string suitValue[]);
    void shuffleDeck(bool deck[]);
    bool again(std::string title);
    void dealAHand(bool deck[], unsigned int hand[5]);
    void displayHand(unsigned int hand[5], std::string suitValue[], std::string faceValue[]);
    void scoreHand(unsigned int hand[5]);
    void checkForHand(  unsigned int faceValue[],
                        unsigned int suitValue[],
                        bool &fourOfAKind,
                        bool &threeOfAKind,
                        unsigned int &pairs,
                        bool &straight,
                        bool &flush,
                        bool &lastTwoAceKing);
    void scoreHand(unsigned int hand[5]);
}

#endif //CS045_POKER_H
