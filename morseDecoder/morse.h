#ifndef CS045_MORSE_H
#define CS045_MORSE_H

#include <iostream>
#include <map>

// todo: move all includes to a single header file

void morse();
std::string& parseMorse();
char& parseChar(const std::string &input);
void getInput();
void loadMorseMap(std::map<std::string, char> myMap, const int standard = 0);


#endif //CS045_MORSE_H
