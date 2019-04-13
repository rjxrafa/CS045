#include "morse.h"

void morse() {
    std::map<std::string, char> myMorseCode;
    loadMorseMap(myMorseCode);

    std::string test = "THIS       IS A STR   ING";
    std::cout << sanitizeInput(test);

    try {
//        std::cout << parseChar(".-", myMorseCode);
//        std::cout << parseChar(".-.", myMorseCode);
//        std::cout << parseChar(".--.", myMorseCode);
//        std::cout << parseChar(".---.", myMorseCode);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "\nAn unknown error has occured." << std::endl;
    }

}

/**
 * This function parses a given morse character as an alphabetical char. Throws an invalid morse char error otherwise.
 * @param input - Takes in a single morse character represented as a string
 * @param morseMap - A map that contains all morse characters mapped to alphanumeric symbols
 * @return - Returns a char literal if successful, else throws an error
 */
char parseChar(const std::string &input, std::map<std::string, char> &morseMap) {
    if (morseMap.count(input))
        return morseMap.at(input);
    else
        throw std::out_of_range("\nInvalid morse character.");
}

/**
 * This function loads a given map with the international morse code.
 * @param myMap
 */
void loadMorseMap(std::map<std::string, char> &myMap) {
//    todo allow for US/morse codes
    myMap[".-"] = 'A';
    myMap["-..."] = 'B';
    myMap["-.-."] = 'C';
    myMap["-.."] = 'D';
    myMap["."] = 'E';
    myMap["..-."] = 'F';
    myMap["--."] = 'G';
    myMap["...."] = 'H';
    myMap[".."] = 'I';
    myMap[".---"] = 'J';
    myMap["-.-"] = 'K';
    myMap[".-.."] = 'L';
    myMap["--"] = 'M';
    myMap["-."] = 'N';
    myMap["---"] = 'O';
    myMap[".--."] = 'P';
    myMap["--.-"] = 'Q';
    myMap[".-."] = 'R';
    myMap["..."] = 'S';
    myMap["-"] = 'T';
    myMap["..-"] = 'U';
    myMap["...-"] = 'V';
    myMap[".--"] = 'W';
    myMap["-..-"] = 'X';
    myMap["-.--"] = 'Y';
    myMap["--.."] = 'Z';
    myMap[".----"] = '1';
    myMap["..---"] = '2';
    myMap["...--"] = '3';
    myMap["....-"] = '4';
    myMap["....."] = '5';
    myMap["-...."] = '6';
    myMap["--..."] = '7';
    myMap["---.."] = '8';
    myMap["----."] = '9';
    myMap["-----"] = '0';
    myMap[".-.-.-"] = '.';
}

std::string sanitizeInput(const std::string &input) {
    std::string temp(input);

    // deletes leading & trailing spaces
    while (temp[0] == ' ')
        temp.erase(0,1);
    while (temp[temp.size()-1] == ' ')
        temp.erase(temp.size()-1);

    // sets all uppercase characters to lower
    for (size_t i = 0 ; i < temp.size(); ++i)
        temp[i] = tolower(temp[i]);

    // This algorithm will replace all instances of 7 spaces with an underscore as a token
    size_t pos = -1;
    while ((pos = temp.find("       ", pos+1)) < temp.size())
    { // careful, we need the pos to be evaluated first, which is why we add the paren
        temp.replace(pos, 7, "__");
    }

    // This algorithm will replace all instances of 3 spaces with an underscore as a token
    pos = -1;
    while ((pos = temp.find("   ", pos+1)) < temp.size())
    { // careful, we need the pos to be evaluated first, which is why we add the paren
        temp.replace(pos, 3, "_");
    }

    return temp;
}
