//
// Created by Rafa on 4/21/2019.
//

#include "poker.h"


void poker::main() {
    std::string faceValue[13];
    const wchar_t* suitValue[4];
    bool deck[52];
    unsigned int hand[5];
    player me;

    initGame(faceValue, suitValue, deck);
    displayGame();

    while(me.coins > 0) {

        displayCoins(&me);
        me.currentBet = playGame(&me);
        me.coins -= me.currentBet;
        dealAHand(deck,hand);
        displayHand(hand, suitValue, faceValue);
        scoreHand(hand, &me);
        displayScore(&me);
        displayCoins(&me);

    }

    exitGame();

}

void poker::loadCardValueAndSuits(std::string *faceValue, const wchar_t **suitValue) {
    suitValue[0] = L"♠"; suitValue[1] = L"♦"; suitValue[2] = L"♣"; suitValue[3] = L"♥";
//    suitValue[0] = "S";
//    suitValue[1] = "D";
//    suitValue[2] = "C";
//    suitValue[3] = "H";
    faceValue[0] = "A";
    faceValue[1] = "2";
    faceValue[2] = "3";
    faceValue[3] = "4";
    faceValue[4] = "5";
    faceValue[5] = "6";
    faceValue[6] = "7";
    faceValue[7] = "8";
    faceValue[8] = "9";
    faceValue[9] = "10";
    faceValue[10] = "J";
    faceValue[11] = "Q";
    faceValue[12] = "K";
}

void poker::shuffleDeck(bool *deck) {
//    std::cout << "Shuffling cards..." << "\n\r";
    for (unsigned int i = 0; i < 52; ++i) {
        deck[i] = false;
    }
}

/**
 * This function takes in a a deck (bool array) and the player's hand (int array). This function stores a static
 * variable for the number of cards that have been dealt by this function. If the number of cards dealt is greater
 * than the reshuffle point, then the function shall reshuffle the given deck before dealing a new hand. In order to
 * deal a new hand, we use the rand function to generate a random number between 0 to 51 which corresponds to a
 * random card in the deck. When a card has been chosen in the deck that hasn't been dealt yet, we deal that
 * new card to the player's hand.
 *
 * @brief This function deals five new cards to a player's hand from a given deck.
 * @param deck
 * @param hand
 */
void poker::dealAHand(bool *deck, unsigned int *hand) {
    unsigned int card, reshufflePoint = 26;
    static unsigned int cardsDealt = 0;
    if (cardsDealt > reshufflePoint) {
        shuffleDeck(deck);
        cardsDealt = 0;
    }
    for (unsigned int i = 0; i < 5; ++i) {
        while(deck[card = rand() % 52]);
        // rand returns a random number between 0 - 51 , which corresponds to a card in the deck. Once a card has
        // been chosen that evaluates to false (have not been dealt), then the loop shall break and we proceed to
        // add this card to the player's hand
        deck[card] = true;
        hand[i] = card;
        ++cardsDealt;
    }

}

void poker::displayHand(unsigned int *hand, const wchar_t **suitValue, std::string *faceValue) {
    int height = 5,
        width = 5+3,
        xpos = 16,
        ypos = 14,
        spacing = 10;

    for (unsigned int i = 0; i < 5; ++i) {
        WINDOW * card = newwin(height, width, ypos, xpos+(spacing*i));
        wbkgd(card, A_STANDOUT);
//        box(card, 0, 0);
        mvwaddstr(card, 0,1, faceValue[hand[i]%13].c_str());
        mvwaddwstr(card, 1,1, suitValue[hand[i]/13]);
        refresh();
        wrefresh(card);
    }

    refresh();

}

void poker::displayScore(poker::player *my) {
    unsigned int height = 3,
                 width = 20,
                 posy = 21,
                 posx = 80/2-width/2;

    WINDOW * score = newwin(height, width, posy, posx);
    box(score, 0,0);
    wrefresh(score);
    refresh();

    if (my->royalStraightFlush) {
        switch (my->currentBet) {
            case 1:
            case 2:
            case 3:
            case 4:
                my->coins += my->currentBet * 250;
            case 5:
                my->coins += my->currentBet * 800;

        }
        mvwprintw(score, 1, width/2-6, "ROYAL FLUSH");

    } else if (my->straight && my->flush) {
        switch (my->currentBet) {
            case 1:
            case 2:
                my->coins += my->currentBet * 50;
            case 3:
            case 4:
            case 5:
                my->coins += my->currentBet * 100;
        }
        mvwprintw(score, 1, width/2-7, "STRAIGHT FLUSH");

    } else if (my->fourOfAKind) {
        my->coins += my->currentBet * 25;
        mvwprintw(score, 1, width / 2 - 6, "4 OF A KIND");

    } else if (my->fullHouse) {
        my->coins += my->currentBet * 9;
        mvwprintw(score, 1, width / 2 - 5, "FULL HOUSE");

    } else if (my->flush) {
        my->coins += my->currentBet * 6;
        mvwprintw(score, 1, width / 2 - 3, "FLUSH");

    } else if (my->straight) {
        my->coins += my->currentBet * 4;
        mvwprintw(score, 1, width / 2 - 4, "STRAIGHT");

    } else if (my->threeOfAKind) {
        my->coins += my->currentBet * 3;
        mvwprintw(score, 1, width / 2 - 6, "3 OF A KIND");

    } else if (my->pairs > 1) {
        my->coins += my->currentBet * 2;
        mvwprintw(score, 1, width / 2 - 3, "2 PAIR");

    } else if (my->highCard) {
        my->coins += my->currentBet;
        mvwprintw(score, 1, width / 2 - 5, "HIGH CARD");
    }
    wrefresh(score);
}

void poker::scoreHand(unsigned int *hand, player *my) {

    resetPlayer(my);

    for (size_t i = 0; i < 5; ++i) {
        ++my->faceValue[hand[i]%13];
        ++my->suitValue[hand[i]/13];
    }

    checkForHand(my);

}

void poker::checkForHand(player *my) {

    // Checks for pairs
    for (size_t i = 0; i < 13; ++i) {
        switch(my->faceValue[i]) {
            case 2: ++my->pairs;
                    break;
            case 3: my->threeOfAKind = true;
                    break;
            case 4: my->fourOfAKind = true;

        }
    }

    // Check for flush (5 cards of the same suit)
    for (size_t j = 0; j < 4; ++j) {
        my->flush |= (my->suitValue[j] == 5);
    }

    // Check for royal flush
    for (size_t k = 0; k < 10 && !my->straight; ++k) {
        // A straight implies that there are 5 '1's in a row, so an & operator on all
        // of them should result in a 1. 0 if the series includes a 0.
        my->straight = my->faceValue[k]   &
                       my->faceValue[k+1] &
                       my->faceValue[k+2] &
                       my->faceValue[k+3] &
                       my->faceValue[(k+4) % 13];

    }

    my->hasAceKing = my->faceValue [12] == 1 &
                     my->faceValue [0] == 1;

    my->highCard |= my->faceValue[0]  | my->faceValue[11] |
                    my->faceValue[10] | my->faceValue[12];

    my->fullHouse = my->threeOfAKind & (my->pairs == 1);

    my->royalStraightFlush = my->hasAceKing & my->straight & my->flush;

}

void poker::initGame(std::string faceValue[52], const wchar_t *suitValue[4], bool deck[52]) {
    initscr();
    setlocale(LC_ALL,"en_US.UTF-8");
//    setlocale(LC_ALL,"");
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    loadCardValueAndSuits(faceValue, suitValue);
    shuffleDeck(deck);

}

void poker::exitGame() {
    endwin();
}

void poker::displayGame() {
    int height = 24;
    int width = 80;
    int xpos = 0;
    int ypos = 0;
    WINDOW * mainWin = newwin(height, width, ypos, xpos);
    box(mainWin, 0,0);
    refresh();
    wrefresh(mainWin);

}

void poker::displayCoins(poker::player *my) {
    int height = 3,
        width = 20,
        ypos = 0,
        xpos = 60;
    WINDOW * coins = newwin(height, width, ypos, xpos);
    box(coins, 0,0);

    mvwprintw(coins, 1,1, "    COINS: %d", my->coins);
    wrefresh(coins);
    refresh();
}

void poker::resetPlayer(poker::player *my) {

    for (auto& x : my->faceValue)
        x = 0;
    for (auto& x : my->suitValue)
        x = 0;

    my->pairs               = 0;
    my->royalStraightFlush  = false;
    my->hasAceKing          = false;
    my->fourOfAKind         = false;
    my->threeOfAKind        = false;
    my->straight            = false;
    my->flush               = false;
    my->fullHouse           = false;
    my->highCard            = false;

}


/**
 * This function creates the bet window that allows the user to input a new bet from 1 to 5.
 * User can use KEY_LEFT and KEY_RIGHT to increment/decrement the bet. Upon pressing KEY_ENTER,
 * the function returns the displayed bet.
 *
 * @return
 */
int poker::playGame(player *me) {
    unsigned int height = 3,
                 width = 16,
                 posy = 0,
                 posx = 0;
    WINDOW * bet = newwin(height, width, posy, posx);
    WINDOW * menu = newwin(height, width, 3, posx+2);
    box(bet, 0, 0);

    unsigned int wager = 1,
                 input;

    mvwprintw(menu, 1,1, "F1 - SAVE"
                         "\n F2 - LOAD");
    mvwprintw(bet, 1,1, "  BET: < %d >", wager);
    wrefresh(bet);
    wrefresh(menu);
    refresh();

    while (1) {
        input = getch();
        switch(input) {
            case KEY_LEFT:
            if (wager > 1)
                --wager;
                break;
            case KEY_RIGHT:
            if (wager < 5)
                wager++;
                break;
            case 10:
                wclear(bet);
                refresh();
                return wager;

            case KEY_F(1):
                saveGame(me);
                break;
            case KEY_F(2):
                loadGame(me);
                break;

            default:
                break;
        }
        mvwprintw(bet, 1,1, "  BET: < %d >", wager);
        wrefresh(bet);
        refresh();
    }

}

/**
 * This function saves the current game state to a file named "poker.dat"
 *
 * @param me
 */
void poker::saveGame(poker::player *me) {

    std::ofstream out;

    unsigned int height = 3,
                 width  = 20,
                 xpos   = getmaxx(stdscr)/2-10,
                 ypos   = 5;


    WINDOW *gameState = newwin(height, width, ypos, xpos);
    box(gameState,0,0);

    out.open("poker.dat");

    if (out.fail()) {
        mvwprintw(gameState, 1, width/2-6, "Save failed!");
    } else {
        mvwprintw(gameState, 1, width/2-5, "Game saved!");
        out << me->coins;
        displayCoins(me);
    }

    wrefresh(gameState);
    refresh();
    getch();
    wclear(gameState);
    refresh();
    out.close();

}

/**
 * This function loads a save state from an input file named poker.dat
 *
 * @param me
 */
void poker::loadGame(poker::player *me) {
    unsigned int height = 3,
                 width = 20,
                 xpos = getmaxx(stdscr)/2-10,
                 ypos = 5;

    WINDOW * gameState = newwin(height, width, ypos, xpos);
    box(gameState,0,0);

    std::ifstream in;

    in.open("poker.dat");

    if (in.fail()) {
        mvwprintw(gameState, 1,width/2-9, "No save file found!");
    } else {
        if (in >> me->coins && me->coins > 0) {
            mvwprintw(gameState, 1,width/2-6, "Game loaded!");

        } else
            mvwprintw(gameState, 1,width/2-6, "Load failed!");
    }

    wrefresh(gameState);
    refresh();
    displayCoins(me);
    getch();
    werase(gameState);
    wrefresh(gameState);
    refresh();



}

void poker::discard() {

}
