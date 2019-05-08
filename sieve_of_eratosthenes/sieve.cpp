/**
 * @brief      This program will take number from the user and will output
 *             all primes up to that given number.
 * @author     Rafael Betita
 * @date       2019-05-07
 */

#include <iostream>
#include "sieve.h"

namespace sieve {

int main() {

    std::vector<int> myPrimes;
    getPrimes(getInput("Enter a number: "), myPrimes);

    for (auto &x : myPrimes)
        std::cout << x << ' ';

    return 0;
}

/**
 * This function allows for user input with some basic input validation for taking in
 * only natural numbers greater than 2.
 *
 * @param        prompt
 * @bug/todo     Takes in characters as their ascii value.
 * @return
 */
int getInput(std::string prompt) {
    int input = -1;

    std::cout << prompt;
    while (std::cin >> input && (input < 1) ) {
        std::cout << "Error, invalid input!\n";
        std::cout << prompt;
    }

    return input;
}

/**
 * This function generates a sequence of prime numbers and stores them into a vector passed
 * as a parameter.
 *
 * @param num generates prime nnumbers up to num as an upper bound
 */
void getPrimes(const int &max, std::vector<int> &v) {

    // create a bool array of the desired size.
    // add+1 to offset numbers by 1, allowing index to correspond to
    // the respective prime number
    bool *arr = new bool[max+1];

    // set all booleans in the array as true,
    // ignoring the first 2 elements (0,1)
    for (int i = 2; i <= max; ++i)
        arr[i] = true;

//    std::cout << "Primes up to " << max << ": " << std:: endl;
    // This algorithm begins the Sieve of Eratosthenes
    for (size_t i = 2; i < max; ++i) {

        // Increment up to a valid prime number
        while (i <= max && !arr[i])
            i++;

        // Print out number if respective value in array is true, making it a prime number
        if (i <= max && arr[i]) {
//            std::cout << ' ' << i;
            v.push_back(i);
        }


        // This forloop will count up to the current max and set all multiples of that
        // prime number as 'false'. This only needs to performed for numbers less than
        // half of the max
        if (i < max/2)
            for (size_t j = i, multiplier = 2; i*multiplier < max; ++j)
                arr[i*multiplier++] = false;


    }

    delete [] arr; // Housekeeping

}

}