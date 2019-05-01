//
// Created by Rafa on 4/21/2019.
//

#include "poker.h"

void poker::main() {
    initGame();
    std::string faceValue[13], suitValue[4];
    bool deck[52];
    unsigned int hand[5];
    srand(time(0));
    loadCardValueAndSuits(faceValue, suitValue);
    shuffleDeck(deck);

    do
    {
        displayMainWindow();
//        dealAHand(deck, hand);
//        displayHand(hand, suitValue, faceValue);
//        hand[0] = 1;hand[1] = 2;hand[2] = 3;hand[3] = 4;hand[4] = 5;
//        scoreHand(hand);
        hand[0] = 13;hand[1] = 23;hand[2] = 25;hand[3] = 24;hand[4] = 22; // flush
//        hand[0] = 12;hand[1] = 32;hand[2] = 34;hand[3] = 26;hand[4] = 13; // flush
        scoreHand(hand);

        displayHand(hand, suitValue, faceValue);

    } while (again("Do you want to do this again? "));
    exitGame();

}

void poker::loadCardValueAndSuits(std::string *faceValue, std::string *suitValue) {
    suitValue[0] = "Spades";
    suitValue[1] = "Diamonds";
    suitValue[2] = "Clubs";
    suitValue[3] = "Hearts";
    faceValue[0] = "Ace";
    faceValue[1] = "Two";
    faceValue[2] = "Three";
    faceValue[3] = "Four";
    faceValue[4] = "Five";
    faceValue[5] = "Six";
    faceValue[6] = "Seven";
    faceValue[7] = "Eight";
    faceValue[8] = "Nine";
    faceValue[9] = "Ten";
    faceValue[10] = "Jack";
    faceValue[11] = "Queen";
    faceValue[12] = "King";
}

void poker::shuffleDeck(bool *deck) {
    std::cout << "Shuffling cards..." << std::endl;
    for (unsigned int i = 0; i < 52; ++i) {
        deck[i] = false;
    }
}

bool poker::again(std::string title) {
    std::string answer;
    std::cout << title << " ";
    std::cin >> answer;
    return toupper(answer[0]) == 'Y';
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
    std::cout << "Your current hand is: \n";
    for (unsigned int i = 0; i < 5; ++i)
        std::cout << faceValue[hand[i]%13] << " of "
                  << suitValue[hand[i]/13];
}

void poker:: scoreHand(unsigned int *hand) {

    playerHand my;


    for (size_t i = 0; i < 5; ++i) {

        ++my.faceValue[hand[i]%13];
        ++my.suitValue[hand[i]/13];
    }

    checkForHand(&my);

    my.fullHouse = my.threeOfAKind & (my.pairs == 1);
    my.royalStraightFlush = my.hasAceKing & my.straight & my.flush;

    if (my.royalStraightFlush)
        std::cout << "Royal straight flush" << std::endl;
    if (my.hasAceKing)
        std::cout << "Last Two Ace King" << std::endl;
    if (my.fourOfAKind)
        std::cout << "Four of a Kind" << std::endl;
    if (my.threeOfAKind)
        std::cout << "Three of a kind" << std::endl;
    if (my.straight)
        std::cout << "Straight" << std::endl;
    if (my.flush)
        std::cout << "Flush" << std::endl;
    if (my.fullHouse)
        std::cout << "Player has full house" << std::endl;
    if (my.pairs)
        std::cout << "Player has " << my.pairs << ((my.pairs == 1) ? " pair" : " pairs") << std::endl;

}

void poker::checkForHand(playerHand *my) {

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

void poker::initGame() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
}

void poker::exitGame() {
    endwin();
}

void poker::displayMainWindow() {
    int height = 22;
    int width = 78;
    int xpos = 1;
    int ypos = 1;
    WINDOW * mainWin = newwin(height, width, ypos, xpos);
    box(mainWin, 0,0);
    refresh();
}
