/**
 * @author  Rafael Betita
 * @date    2019-04-14
 *
 * @brief   This program simulates a seven segment display by creating a relation
 *          between the numbers 0 to 9 and their corresponding segments (from 0 to 6)
 *          required to display the digit.
 */

#ifndef CS045_DISPLAY_H
#define CS045_DISPLAY_H

#include <map>
#include <iostream>
#include <bitset>

namespace seg_display{

void display();
bool getInput(std::string userInput);
void loadSegmentMap(std::map<int, std::bitset<7>> &mySegmentMap);
void displaySegment(std::bitset<7> &printMe, std::ostream &os);

};

#endif //CS045_DISPLAY_H
