#include "display.h"

/**
 * @brief   This is the main function to call when running the program.
 *
 * @bug     This implementation allows for multiple digits, but will perform undefined behavior
 *          when passing invalid inputs such as "123a3"
 */
void seg_display::display() {

    try {
        std::map<int, std::bitset<7>> myMap;
        loadSegmentMap(myMap);
        std::string userInput;

        while(getInput(userInput)) {
            for (size_t i = 0; i < userInput.length(); ++i) {
                displaySegment(myMap[userInput[i]-48], std::cout);
            }
        }

    } catch(...) {
        std::cout << "\nAn unknown error has occurred.\n" << std::endl;
    }
}

/**
 * This function validates user input.
 * @param userInput Parameter to be modified
 * @return bool returns false if string was empty or an invalid input.
 */
bool seg_display::getInput(std::string &userInput) {

    std::cout << "\nEnter a number to be translated: ";
    getline(std::cin, userInput);
    fflush(stdin);

    std::stringstream ss(userInput);
    unsigned int temp;

    // todo: bug with certain inputs such as "123a4"
    if (ss >> temp)
        return true;
    else {
        std::cout << "\nInvalid input. Exiting program.";
        return false;
    }
}

/**
 * This function loads a map with the relation between integers and its corresponding segment bits.
 * @param mySegmentMap
 */
void seg_display::loadSegmentMap(std::map<int, std::bitset<7>> &mySegmentMap) {
    mySegmentMap[0] = std::bitset<7>("0111111");
    mySegmentMap[1] = std::bitset<7>("0000110");
    mySegmentMap[2] = std::bitset<7>("1011011");
    mySegmentMap[3] = std::bitset<7>("1001111");
    mySegmentMap[4] = std::bitset<7>("1100110");
    mySegmentMap[5] = std::bitset<7>("1101101");
    mySegmentMap[6] = std::bitset<7>("1111101");
    mySegmentMap[7] = std::bitset<7>("0000111");
    mySegmentMap[8] = std::bitset<7>("1111111");
    mySegmentMap[9] = std::bitset<7>("1100111");
}

/**
 * This function takes in a bitset that displays the corresponding
 * segments to the given output stream.
 * @param printMe is a bitset that corresponds to certain segments to be printed
 */
void seg_display::displaySegment(std::bitset<7> &printMe, std::ostream &os) {
    char segments[7];

    // Loads corresponding segment with identifier, depending on whether bit was turned on
    for (size_t i = 0; i < 7; ++i) {
        segments[i] = printMe[i] ? '#' : ' ';
    }

    // Segment 0
    os << " " + std::string(5, segments[0]) + " " << std::endl;

    // Segment 1-2
    os << segments[5] + std::string(5, ' ') + segments[1] << std::endl;
    os << segments[5] + std::string(5, ' ') + segments[1] << std::endl;

    // Segment 3
    os << " " + std::string(5, segments[6]) + " " << std::endl;

    // Segment 4-5
    os << segments[4] + std::string(5, ' ') + segments[2] << std::endl;
    os << segments[4] + std::string(5, ' ') + segments[2] << std::endl;

    // Segment 6
    os << " " + std::string(5, segments[3]) + " " << std::endl;

}
