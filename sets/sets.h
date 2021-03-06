// Created by Rafa on 3/27/2019.
// Adapted from Paul Wilkinson's CS045 lectures.

#ifndef CS045_SETS_H
#define CS045_SETS_H

#include <iostream>
#include <map>
#include <bitset>

using namespace std;

int sets(); // This is our main function for the assignment
bool getLine(string &line);
string display(const bitset<16> &set);
//void process(string line, uint16_t &set);
void process(string line, const map<string, int> &commands, map<char, bitset<16>> &mySets);
void loadCommands(map<string, int> &commands);
void trimLineAndStandardize(string &line);
void findCommand(const string &line, string &command, string &suffix);
void executeCommand(const string &command,
                    const string &suffix,
                    const map<string, int> &commands,
                    map<char, bitset<16>> &mySets);
void helpMe(ostream &out);
void listSets(ostream &out, map<char, bitset<16>> &mySets);
void modifySet(const string &suffix, map<char,bitset<16>> &mySets);
bitset<16> returnBitset(string &suffix);
void loadSets(map<char, bitset<16>> &mySets);


#endif //CS045_SETS_H
