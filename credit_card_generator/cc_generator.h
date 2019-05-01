//
// Created by Rafa Betita on 2019-04-30.
//

#ifndef CS045_CC_GENERATOR_H
#define CS045_CC_GENERATOR_H

#include <iostream>
#include <fstream>
#include <sstream>

namespace cc_gen {
    enum bank {
        AMERICAN_EXPRESS = 3,
        VISA = 4,
        MASTERCARD = 5,
        DISCOVER = 6
    };
    int main ();
    int checkDigit(const std::string &account);
    std::string generateValidCard(const bank &myBank);

}

#endif //CS045_CC_GENERATOR_H
