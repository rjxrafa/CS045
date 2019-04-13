#include "morse.h"

void morse() {
    std::map<std::string, char> myMorseCode;
    loadMorseMap(myMorseCode);


}

std::string &parseMorse() {
//    return <#initializer#>;
}

char &parseChar(const std::string &input) {
//    return <#initializer#>;
}

void getInput() {

}

void loadMorseMap(std::map<std::string, char> myMap, const int standard){
//    todo allow for international/US/morse codes
    if (standard == 1)
    {
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
//        myMap["--..--"] =
    }
}
