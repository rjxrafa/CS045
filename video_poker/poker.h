/**
 * This program was adapted from Paul Wilkinson's CS045 lectures.
 */

#ifndef CS045_POKER_H
#define CS045_POKER_H

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <locale.h>
#include <ncursesw/ncurses.h>

namespace poker{

    struct player {
        int coins = 500;
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
    void loadCardValueAndSuits(std::string faceValue[], wchar_t *suitValue[]);
    void shuffleDeck(bool deck[]);
    bool again(std::string title);
    void dealAHand(bool deck[], unsigned int hand[5]);
    void scoreHand(unsigned int hand[5], player *my);
    void displayHand(unsigned int hand[5], wchar_t **suitValue, std::string faceValue[]);
    void displayCoins(player *my);
    void displayScore(player *my);
    void displayGame();
    void checkForHand(player *my);
    void initGame(std::string faceValue[13], wchar_t *suitValue[4], bool deck[52]);
    void exitGame();
    bool playGame();
    void resetPlayer(player *my);
    int makeBet();



}

#endif
#endif //CS045_POKER_H
