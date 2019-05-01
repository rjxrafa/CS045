//
// Created by Rafa Betita on 2019-04-30.
//

#include "cc_generator.h"

/**
 * This main function will call the generator 100,000 times to generate and output to a valid_cards.txt
 * file. All generated cards will be using a VISA IIN (starts with 4).
 *
 * @return 0 for successful operation
 */
int cc_gen::main() {

    srand(time(nullptr));

    std::ofstream out("valid_cards.txt");
    for (size_t i = 0; i < 100000; ++i)
        out <<  generateValidCard(VISA) << std::endl;

    out.close();

    return 0;
}

/**
 * This function will take in a string and return its valid check digit as an integer
 *
 * @param account as {string}
 * @return check digit as {int}
 */
int cc_gen::checkDigit(const std::string &account) {

    int sum = 0;
    // Go through all the digits from right to left,
    // starting from the 2nd digit
    for (int i = 14; i >= 0; --i) {
    // Double all digits to add to a sum
    // If the doubled digit is greater than 10, then
    // add the two digit product's digits together to
    // create a new digit to add to the sum
        sum += ((i+1)%2) ? // for every other num, double
                (account[i]-'0')*2 > 9 ? // for digits greater than 9,
                    (account[i]-'0')*2-9 : (account[i]-'0')*2 : // add digits together, else leave prduct
                (account[i]-'0'); // else just add the number
//        std::cout << account[i] << std::endl;
    }
    sum *= 9;

    return (sum%10);
}

/**
 * This function will generate a valid credit card number as a string, depending on the desired bank as input.
 *
 * @param myBank {enum} type established in the header file, establishes the IIN
 * @return valid credit card number as a {string}
 */
std::string cc_gen::generateValidCard(const bank &myBank) {

    std::stringstream ss;

    // todo: handle more IIN types, which have varying lengths for cards
    // see: https://en.wikipedia.org/wiki/Payment_card_number#Major_Industry_Identifier_.28MII.29
    switch (myBank) {
        case AMERICAN_EXPRESS:
            ss << 3;
            break;
        case VISA:
            ss << 4;
            break;
        case MASTERCARD:
            ss << 5;
            break;
        case DISCOVER:
            ss << 6;
            break;
        default:
            ss << 0;
            break;

    }

    // Create 14 more digits for the credit card number
    for (size_t i = 0; i < 14; ++i)
        ss << (rand() % 10);

    ss << checkDigit(ss.str()); // Create a valid check digit as the last digit

    return ss.str();
}
