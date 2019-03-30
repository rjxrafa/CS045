/**
 * @author  Rafael Betita
 * @date    2019-03-30
 *
 *  This assignment was adapted from Paul Wilkinson's CS045 lectures. See header for more info on implementation.
 */

#include "alternate_if_else.h"

int alternateIfElse() {
    string line, charsWeWant;
    loadCharsWeWant(charsWeWant);
    while(getInput(line))
        (normalize(line, charsWeWant) && invalidInput(line)) || process(line);
    // (If normalize returns false, then it will skip invalid input. Otherwise, it will
    // call invalidInput (which returns true, therefore making that first proposition true and
    // skips the evaluation of process. Otherwise, if either one is false, we process the line.

    cout << line << endl;
    return 1;
}

bool getInput(string &line) {
    cout << "Your name: ";
    getline(cin, line);
    fflush(stdin);
    return !line.empty();
}

bool normalize(string &line, const string &charsWeWant) {
    trimSpaces(line);
    for (size_t i = 0; i < line.size(); i++)
        line[i] = tolower(line[i]);

    size_t pos = -1, spaceCount = 0;
    while((pos = line.find(' ', pos+1)) < line.size())
        spaceCount++;

    return (line.find_first_not_of(charsWeWant) < line.size() || (spaceCount > 2));
}

bool hasMiddleInitial(string &line) {
    return false;
}

void trimSpaces(string &line) {
    while (line[0] == ' ')
        line.erase(0,1);
    while(line[line.size()-1] == ' ')
        line.erase(line.size()-1);
    size_t pos = -1;

    while((pos = line.find(' ', pos+1)) < line.size())
    {
        while(line[pos+1] == ' ')
            line.erase(pos+1, 1);
    }
}

void loadCharsWeWant(string &chars) {
    for (char want = 'A'; want <= 'Z'; ++want) {
        chars += want;
        chars += tolower(want);
    }
    chars += ' ';
}

bool invalidInput(const string &line) {
    cout << "Detected invalid input after trying to normalize. Invalid characters are in " << line << endl;
    return true;
}

bool process(string &line) {
    unsigned int lastSpace = line.find_last_of(' ');
    string lastName = line.substr(lastSpace+1), restOfName = line.substr(0, lastSpace);
    capitalizeFirstChar(lastName);
    capitalizeFirstChar(restOfName);
    lastName += ", ";
    line = lastName + restOfName;
    cout << "Your name is: " << line << endl;
    return true;
}

void capitalizeFirstChar(string &name) {
    name[0] = toupper(name[0]);
    unsigned int pos = 0;
    while ((pos = name.find(' ', pos)) < name.size())
        name[++pos] = toupper(name[pos]);
}
