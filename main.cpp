#include <iostream>
#include "sets/sets.h"
#include "alternate_if_then_else/alternate_if_else.h"
#include "morse_decoder/morse.h"
#include "seven_segment_display/display.h"

int main() {
//
//    sets();
//    alternateIfElse();
//    morse::morse();
    std::bitset<7> test("1111111");
    seg_display::displaySegment(test, cout);



    return 0;
}