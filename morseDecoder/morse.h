#ifndef CS045_MORSE_H
#define CS045_MORSE_H

#include <iostream>
#include <map>
#include <exception>

// todo: move all includes to a single header file

void morse();
void getInput();
std::string& parseMorse();
char parseChar(const std::string &input, std::map<std::string, char> &morseMap);
void loadMorseMap(std::map<std::string, char> &myMap);


#endif //CS045_MORSE_H
