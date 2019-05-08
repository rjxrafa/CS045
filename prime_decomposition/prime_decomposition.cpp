//
// Created by rafab on 5/7/2019.
//

#include "prime_decomposition.h"

int decomposition::main() {

    decompose(sieve::getInput("Enter a number: "));

}

/**
 * This function takes in any number and decomposes it as its prime constituents.
 * @param num
 */
void decomposition::decompose(const int &num) {
    std::vector<int> myPrimes;
    int temp = num;

    sieve::getPrimes(num, myPrimes);
//    for
    for (unsigned int i = 0; temp != 1; ++i) {
        if (!(temp % myPrimes[i])) {
            while (!(temp % myPrimes[i])) {
                temp /= myPrimes[i];

                std::cout << myPrimes[i] << ' ';
            }
        }
    }
}

