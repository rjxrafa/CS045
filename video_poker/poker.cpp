//
// Created by Rafa on 4/21/2019.
//

#include "poker.h"

void poker::main() {
    std::string faceValue[13], suitValue[4];
    bool deck[52];
    unsigned int hand[5];

    initGame(faceValue, suitValue, deck);
    player me;

    srand(time(0));

    do
    {
        displayGame();
        dealAHand(deck, hand);
//        hand[0] = 1;hand[1] = 2;hand[2] = 3;hand[3] = 4;hand[4] = 5;
//        hand[0] = 13;hand[1] = 23;hand[2] = 25;hand[3] = 24;hand[4] = 22; // flush
//        hand[0] = 12;hand[1] = 32;hand[2] = 34;hand[3] = 26;hand[4] = 13; // flush
        displayCoins(&me);
        me.coins--;
        scoreHand(hand, &me);
        displayHand(hand, suitValue, faceValue);

    } while (playGame());
    exitGame();

}

void poker::loadCardValueAndSuits(std::string *faceValue, std::string *suitValue) {
//    suitValue[0] = "♠";
//    suitValue[1] = "♦";
//    suitValue[2] = "♣";
//    suitValue[3] = "♥";
    suitValue[0] = "S";
    suitValue[1] = "D";
    suitValue[2] = "C";
    suitValue[3] = "H";
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

bool poker::again(std::string title) {
    int height = 3,
        width = title.length()+2,
        ypos = 5,
        xpos = 22;
    WINDOW * prompt = newwin(height, width, ypos, xpos);
    box(prompt,1,1);
    mvwprintw(prompt, 1,1, title.c_str());
    wrefresh(prompt);
    return toupper(getch()) == 'Y';
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

void poker::displayHand(unsigned int *hand, std::string *suitValue, std::string *faceValue) {
    int height = 6,
        width = 5+3,
        xpos = 15,
        ypos = 16,
        spacing = 10;

    for (unsigned int i = 0; i < 5; ++i) {
        WINDOW * card = newwin(height, width, ypos, xpos+(spacing*i));
        box(card, 0, 0);
        mvwaddstr(card, 1,1, faceValue[hand[i]%13].c_str());
        mvwaddstr(card, 2,1, suitValue[hand[i]/13].c_str());

        refresh();
        wrefresh(card);
    }




    refresh();

}

void poker::displayScore(poker::player *my) {
    unsigned int height = 3,
                 width = 10,
                 posy = 0,
                 posx = 0;

    WINDOW * score = newwin(height, width, posy, posx);
    box(score, 0,0);
    wrefresh(score);

    //    if (my->royalStraightFlush)
//        std::cout << "Royal straight flush" << "\n\r";
//    if (my->hasAceKing)
//        std::cout << "Last Two Ace King" << "\n\r";
//    if (my->fourOfAKind)
//        std::cout << "Four of a Kind" << "\n\r";
//    if (my->threeOfAKind)
//        std::cout << "Three of a kind" << "\n\r";
//    if (my->straight)
//        std::cout << "Straight" << "\n\r";
//    if (my->flush)
//        std::cout << "Flush" << "\n\r";
//    if (my->fullHouse)
//        std::cout << "Player has full house" << "\n\r";
    if (my->pairs > 1) {
        my->coins+=2;
        clrtoeol();
    }

    move(10,10);
    mvprintw(10,10, "my pairs %d", my->pairs);
//        std::cout << "Player has " << my.pairs << ((my.pairs == 1) ? " pair" : " pairs") << "\n\r";

}

void poker::scoreHand(unsigned int *hand, player *my) {

    resetPlayer(my);

    for (size_t i = 0; i < 5; ++i) {

        ++my->faceValue[hand[i]%13];
        ++my->suitValue[hand[i]/13];
    }

    checkForHand(my);

    my->fullHouse = my->threeOfAKind & (my->pairs == 1);
    my->royalStraightFlush = my->hasAceKing & my->straight & my->flush;

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
        my->flush |= my->suitValue[j] == 5;
    }
    //     unsigned int faceValue[13] = {1,0,0,0,0,0,0,0,0,1,1,1,1},
    // Check for royal flush
    for (size_t k = 0; k < 10 && !my->straight; ++k) {
        // A straight implies that there are 5 '1's in a row, so an & operator on all of them should result in a 1.
        // 0 if the series includes a 0.
        my->straight = my->faceValue[k]   &
                       my->faceValue[k+1] &
                       my->faceValue[k+2] &
                       my->faceValue[k+3] &
                       my->faceValue[(k+4) % 13];
    }
    my->hasAceKing = my->faceValue [12] == 1 &
                     my->faceValue [0] == 1;
}

void poker::initGame(std::string faceValue[52], std::string suitValue[4], bool deck[52]) {
    initscr();
    setlocale(LC_ALL,"");
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
    wrefresh(mainWin);
    refresh();
}

void poker::displayCoins(poker::player *my) {
    int height = 3,
        width = 20,
        ypos = 1,
        xpos = 59;
    WINDOW * coins = newwin(height, width, ypos, xpos);
    box(coins, 0,0);

    mvwprintw(coins, 1,1, "COINS: %d", my->coins);
    wrefresh(coins);

}

bool poker::playGame() {
    unsigned int height = 3,
                 width = 15,
                 posy = 0,
                 posx = 0;
    WINDOW * bet = newwin(height, width, posy, posx);
    box(bet, 0, 0);

    unsigned int wager = 1,
                 input;
    input = getch();
    switch(1) {
        case KEY_LEFT:
            if (wager > 1)
                --wager;
            break;
        case KEY_RIGHT:
            if (wager < 5)
                wager++;
            break;
        case KEY_F(1):
        case 10:
            return false;

        default:
            break;
    }
    mvwprintw(bet, 1,1, "  Bet: < %d >", wager);
    wrefresh(bet);

    return true;
}

void poker::resetPlayer(poker::player *my) {
    for (auto& x : my->faceValue)
        x = 0;
    for (auto& x : my->faceValue)
        x = 0;

    my->pairs = 0;
    my->royalStraightFlush = false;
    my->hasAceKing = false;
    my->fourOfAKind = false;
    my->threeOfAKind = false;
    my->straight = false;
    my->flush = false;
    my->fullHouse = false;
}
