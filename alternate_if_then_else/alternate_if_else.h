/**
 * @brief  This program will take a given input for a user's name and normalizes the input.
 * @author  Rafael Betita
 * @date 2019-03-29
 *
 * This assignment was adapted from Paul Wilkinson's CS045 lectures. The program expects an
 * unformatted input for the user's first and last name (optionally middle initial) and outputs
 * a formatted string as {LastName, FirstName Initial}. Any leading or trailing spaces are omitted.
 *
 * @example
 * Your name: rafael betita
 * Your name is: Betita, Rafael
 * Your name: Paul  J    wiLkinsoN
 * Your name is: Wilkinson, Paul J
 * Your name: Rafael L L L Betita
 * Detected invalid input after trying to normalize. Invalid characters are in rafael l l l betita
 * Your name: 1234
 * Detected invalid input after trying to normalize. Invalid characters are in 1234
 */

#ifndef CS045_ALTERNATE_IF_ELSE_H
#define CS045_ALTERNATE_IF_ELSE_H

#include <iostream>

using namespace std;

int alternateIfElse(); // Main driver function
bool getInput(string &line);
bool normalize(string &line, const string &charsWeWant);
bool hasMiddleInitial(string &line); // todo: implement middle initial func
void trimSpaces(string &line);
void loadCharsWeWant(string &chars);
bool invalidInput(const string &line);
bool process(string &line);
void capitalizeFirstChar(string &name);

#endif //CS045_ALTERNATE_IF_ELSE_H
