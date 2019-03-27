// Created by Rafa on 3/27/2019.
// Adapted from Paul Wilkinson's CS045 lectures.

#ifndef CS045_SETS_H
#define CS045_SETS_H

#include <iostream>
#include <map>

using namespace std;

int sets(); // This is our main function for the assignment
bool getLine(string &line);
void display(uint16_t set);
void process(string line, uint16_t &set);
void process(string line, const map<string, int> &commands);
void loadCommands(map<string, int> &commands);
void trimLineAndStandardize(string &line);
void findCommand(const string &line, string &command, string &suffix);
void executeCommand(const string &command, const string &suffix, const map<string, int> &commands);


#endif //CS045_SETS_H
