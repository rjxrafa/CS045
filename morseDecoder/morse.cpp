#include "morse.h"

void morse() {
    std::map<std::string, char> myMorseCode;
    loadMorseMap(myMorseCode);

    try {
        std::cout << parseChar(".-", myMorseCode);
        std::cout << parseChar(".-.", myMorseCode);
        std::cout << parseChar(".--.", myMorseCode);
        std::cout << parseChar(".---.", myMorseCode);
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

std::string &parseMorse() {
//    return <#initializer#>;
}

char parseChar(const std::string &input, std::map<std::string, char> &morseMap) {
    if (morseMap.count(input))
        return morseMap.at(input);
    else
        throw std::out_of_range("\nInvalid morse character.");
}

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
