//
// Created by Rafa on 4/21/2019.
//

#include "poker.h"

void poker::main() {
    std::string faceValue[13], suitValue[4];
    bool deck[52];
    unsigned int hand[5];
    srand(time(0));
    loadCardValueAndSuits(faceValue, suitValue);
    shuffleDeck(deck);

    do
    {
        dealAHand(deck, hand);
        displayHand(hand, suitValue, faceValue);
        hand[0] = 1;
        hand[1] = 2;
        hand[2] = 3;
        hand[3] = 4;
        hand[4] = 5;
        scoreHand(hand);
    } while (again("Do you want to do this again? "));

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
        std::cout << faceValue[hand[i]%13] << " of " << suitValue[hand[i]/13] << std::endl;
    std::cout << std::endl << std::endl;
}

void poker:: scoreHand(unsigned int *hand) {
    unsigned int faceValue[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0},
                 suitValue[4] = {0,0,0,0},
                 pairs = 0;
    bool royalStraightFlush = false,
         lastTwoAceKing = false,
         fourOfAKind = false,
         threeOfAKind = false,
         straight = false,
         flush = false,
         fullHouse = false;

    for (size_t i = 0; i < 5; ++i) {
        ++faceValue[hand[i]%13];
        ++suitValue[hand[i]/13];
    }

    checkForHand(faceValue, suitValue, fourOfAKind, threeOfAKind, pairs, straight, flush, lastTwoAceKing);

    fullHouse = threeOfAKind & (pairs == 1);
    royalStraightFlush = lastTwoAceKing & straight & flush;

    if (royalStraightFlush)
        std::cout << "Royal straight flush" << std::endl;
    if (lastTwoAceKing)
        std::cout << "Last Two Ace King" << std::endl;
    if (fourOfAKind)
        std::cout << "Four of a Kind" << std::endl;
    if (threeOfAKind)
        std::cout << "Three of a kind" << std::endl;
    if (straight)
        std::cout << "Straight" << std::endl;
    if (flush)
        std::cout << "Flush" << std::endl;
    if(fullHouse)
        std::cout << "Player has full house" << std::endl;
    if (pairs)
        std::cout << "Player has " << pairs << ((pairs == 1) ? " pair" : " pairs") << std::endl;

}

void poker::checkForHand(unsigned int *faceValue, unsigned int *suitValue, bool &fourOfAKind, bool &threeOfAKind,
                         unsigned int &pairs, bool &straight, bool &flush, bool &lastTwoAceKing) {
    threeOfAKind = fourOfAKind = false;
    pairs = 0;
    straight = flush = false;

    // Checks for pairs
    for (size_t i = 0; i < 13; ++i) {
        switch(faceValue[i]) {
            case 2: ++pairs;
                    break;
            case 3: threeOfAKind = true;
                    break;
            case 4: fourOfAKind = true;

        }
    }
    
    // Check for flush
    for (size_t j = 0; j < 4; ++j) {
        flush |= suitValue[j] == 4;
    }

    // Check for flush
    for (size_t k = 0; k < 9 && !straight; ++k) {
        straight = faceValue[k] &
                   faceValue[k+1] &
                   faceValue[k+2] &
                   faceValue[k+3] &
                   faceValue[k+4 % 13];
        lastTwoAceKing = faceValue [k+3]%13 == 12 &
                         faceValue [(k+3%13)] == 0;
    }
}


