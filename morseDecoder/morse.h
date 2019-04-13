#ifndef CS045_MORSE_H
#define CS045_MORSE_H

#include <iostream>
#include <map>
#include <exception>
#include <sstream>

// todo: move all includes to a single header file

namespace morse {
    void morse();
    bool getInput(std::string& input);
    std::string sanitizeInput(const std::string &input);
    char parseChar(const std::string &input, std::map<std::string, char> &morseMap);
    std::string parseMorse(const std::string &input, std::map<std::string, char> &myMorseMap);
    void loadMorseMap(std::map<std::string, char> &myMap);
}

#endif //CS045_MORSE_H
