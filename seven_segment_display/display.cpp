#include "display.h"

void seg_display::display() {

}

bool seg_display::getInput(std::string userInput) {
    return false;
}

void seg_display::loadSegmentMap(std::map<int, std::bitset<7>> &mySegmentMap) {

}

/**
 * This function takes in a bitset that displays the corresponding
 * segments to the given output stream.
 * @param printMe
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

    // Row 3
    os << " " + std::string(5, segments[6]) + " " << std::endl;

    // Segment 4-5
    os << segments[4] + std::string(5, ' ') + segments[2] << std::endl;
    os << segments[4] + std::string(5, ' ') + segments[2] << std::endl;

    // Segment 6
    os << " " + std::string(5, segments[3]) + " " << std::endl;

}
