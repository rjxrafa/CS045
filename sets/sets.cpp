/**
 * @brief   This assignment encompasses the sets lecture from Paul Wilkinson's Spring 2019 CS045 class.
 * @author  Rafael Betita
 * @date    2019-03-29
 */

#include <sstream>
#include <assert.h>
#include <vector>
#include "sets.h"

int sets() {
    string line;
    map<string, int> commands;
    map<char, bitset<16>> mySets;

    loadSets(mySets);
    loadCommands(commands);

    while (getLine(line))
        process(line, commands, mySets);

    return 0;
}

bool getLine(string &line) {
    cout << "Command: ";
    getline(cin, line);
    fflush(stdin);
    return !line.empty();
}

/**
 * @brief This function will take in a bitset and display the set as a representation of integer values.
 * @param set A given bitset
 * This function takes in a bitset<16> value which converts each bit in the set as an integer representation of that
 * bit's value. Each bit in the bitset represents an individual value between 0-15, which corresponds to the positional
 * value of the bit.
 *
 * @example
 * bitset<16> a("0011")
 * bitset<16> b("1001")
 * cout << display(a); // Displays '1,2'
 * cout << display(b); // Displays '1,8'
 */
string display(const bitset<16> &set) {
    string temp;

    for (uint8_t i = 0; i < set.size(); ++i) {
        if (set[i]) { // If that current bit's value is 1, then add it to the string
            temp += to_string(i);
            temp += ',';
        }
    }

    if (temp.back() == ',')
        temp.pop_back();


    return temp;

}

//void process(string line, uint16_t &set) {
//    try {
//        set = stoi(line);      // todo: input validation, should be less than uint16_t max
//    } catch (...) {
//        cout << "Invalid input found\n";
//        return;
//    }
//
//    set = ~set;
//    cout << "Compliment: ";
//    display(set);
//}

/**
 * @brief           Processes commands for execution
 * @param line      User input as a string
 * @param commands  Preloaded list of commands to be accessed
 * @param mySets    Preloaded list of sets to be modified
 *
 * This function takes in a user's input (e.g. SET C = A * B) and processes the given line to be executed.
 * The function will firstly trim the line for extra spaces within the input and consequently will display the
 * sanitized line. Afterwards, the function calls findCommand, which takes in 2 strings (command, suffix) to be
 * executed using the executeCommand, which takes in the newly formed command and suffix as well as the commands map.
 */
void process(string line, const map<string, int> &commands, map<char, bitset<16>> &mySets){
    string command, suffix;
    cout << "Processing...\n";
    trimLineAndStandardize(line);
    cout << line << endl;
    findCommand(line, command, suffix);
    cout << "Command: " << " Suffix: " << suffix << endl;
    executeCommand(command, suffix, commands, mySets);
}

/**
 * @brief This function takes in an empty map<string,int> of commands to store predefined keys and values to.
 * @param commands Takes in the reference for an empty map to preload key & value pairs to.
 */
void loadCommands(map<string, int> &commands) {
    commands["LOAD"] = 0;
    commands["SAVE"] = 1;
    commands["SET"]  = 2;
    commands["HELP"] = 3;
    commands["LIST"] = 4;
    commands["EXIT"] = 5;
}

/**
 * @brief Trims and standardizes a given string.
 * @param line {string} to be trimmed and standardized
 * @return void
 *
 * This function trims an input string for leading/trailing spaces and sets all
 * characters to uppercase.
 */
void trimLineAndStandardize(string &line) {
    size_t pos = -1; // 4294967295
    while (line[0] == ' ') // Erase leading spaces
        line.erase(0,1);
    while(line[line.size()-1] == ' ') // Erase trailing spaces
        line.erase(line.size()-1);
    while ((pos = line.find(' ', ++pos)) < line.size()) // Search for any space within the string
        while(line[pos+1] == ' ') // If any double spaces are found, delete the extra space
            line.erase(pos+1,1); // Delete up to 1 neighboring character
    for(size_t i = 0; i < line.size(); ++i) // Set string to uppercase, if applicable
        line[i] = toupper(line[i]);
}

/**
 * @brief Takes in a input line and tokenizes the command and suffix delimited by a space.
 * @param line A given input line containing a command and suffix, separated by a space
 * @param command Reference to the command string to be stored into
 * @param suffix Reference to the suffix string to be stored into
 * @todo Add bool success state
 */
void findCommand(const string &line, string &command, string &suffix) {
    size_t pos = line.find(' ');
    if (pos < line.size()) {
        command = line.substr(0, pos);
        suffix = line.substr(pos+1);
    }
    else {
        command = line;
        suffix = "";
    }
}

/**
 * @brief Executes a given command and passing the suffix as a parameter using a map containing each command.
 * @param command a reference to the command string
 * @param suffix  a reference to the suffix string
 * @param commands a map to a list of preloaded commands to be executed
 */
void executeCommand(const string &command,
                    const string &suffix,
                    const map<string, int> &commands,
                    map<char, bitset<16>> &mySets) {

    int whatToDo;
    if (commands.count(command))
        whatToDo = commands.at(command);
    else
        whatToDo = 99;

    switch(whatToDo) {
        case 0: // LOAD
            break;
        case 1: // SAVE
            break;
        case 2: // SET
            modifySet(suffix, mySets);
            break;
        case 3: // HELP
            helpMe(cout);
            break;
        case 4: // LIST
            listSets(cout, mySets);
            break;
        case 5: // EXIT
            cout << "\nExiting program. Thanks!";
            exit(1);
        default:
            cout << "Invalid command!\n";
    }

}

/**
 * @brief This function takes in an output stream and displays a help page.
 * @param out Output stream to be printed to.
 */
void helpMe(ostream &out) {
    out << "\nWelcome to the Set Calculator!\n";
    out << "\nThis program allows users to modify sets and perform operations between two given sets.\n";
    out << "\nList of commands:\n"
           "LIST - List all sets and their contents.\n"
           "HELP - Show this help page.\n"
           "SET  - Modify an existing set (A,B,C) and allow for definitions, unions, intersections, or a combination. \n"
           "LOAD - Load an existing configuration from a saved file.\n"
           "SAVE - Save the current configuration to a text file.\n";
    out << "\nAccepted Inputs:\n"
           "SET A = {1,2,3}\n"
           "SET B = {3,4,5}\n"
           "SET C = A + B\n"
           "SET C = A * B\n"
           "SET A = B\\C\n"
           "SET A = {1,2,3}\\{2,3}\n";
}

/**
 * @brief This function takes in an ostream and outputs the current values for all available sets.
 * @param out Output stream to be printed to.
 */
void listSets(ostream &out, map<char, bitset<16>> &mySets) {
    out << "SET A = {" << display(mySets['A']) << "}\n";
    out << "SET B = {" << display(mySets['B']) << "}\n";
    out << "SET C = {" << display(mySets['C']) << "}\n";
}

/**
 * @brief This function modifies a set using the suffix passed as a string.
 * @param suffix An argument passed containing which set to modify with a corresponding RHS value
 *
 * This function handles several operations based on the suffix string provided.
 *
 * @example
 * A = {1,2,3} // Modify set A's domain
 * B = {3} // Modify set B's domain
 * C = A+B // Modify set C's domain based on the union of A&B
 * C = A*B // Modify set C's domain based on the intersection of A&B
 * C = ~A // Modify set C's domain based on A's complement
 * C = ~{1,2,3} // Modify set C's domain based on the given complement
 * C = B\C // Modify set C's domain based on the set difference of B\C
 * C = {n}\{n}// Modify set C's domain based on the set difference of the first and second set
 */
void modifySet(const string &suffix, map<char, bitset<16>> &mySets) {
// todo: complement of an empty set error
// todo: input validation ~{A+B}?
// todo: this takes in duplicate set items
// todo: this allows for missing curly brackets

    stringstream ss(suffix);
    char modifyThisSet;
    ss >> modifyThisSet;
    if(mySets.count(modifyThisSet)) {
        char temp(0);
        int setValue(0);
        bitset<16> userSet(0);
        ss >> temp >> temp; // This assumes that =  and "{" are getting picked up. todo: "~"
        while (ss >> setValue) {
            if (setValue > 15u) {
                cout << "Invalid number found";
                return;
            } else {
                userSet[setValue] = true;
            }
            if (ss.peek() == ',')
                ss.get();
        }
        mySets[modifyThisSet] = userSet;
        cout << "Succesfully modified set " << modifyThisSet << endl;

    } else {
        cout << "Set not found" << endl;
        return;
    }




}

bitset<16> returnBitset(string &suffix) {
    bitset<16> temp;
    size_t pos = -1;


    return temp;
}

void loadSets(map<char, bitset<16>> &mySets) {
    mySets['A'] = 0;
    mySets['B'] = 0;
    mySets['C'] = 0;
}

