/**
 * @brief This assignment encompasses the sets lecture from Paul Wilkinson's Spring 2019 CS045 class.
 * @author Rafael Betita
 * @date 2019-03-27
 */

#include "sets.h"

int sets() {
    string line;
    uint16_t set = 0;

    while (getLine(line))
        process(line, set);

    return 0;
}

bool getLine(string &line) {
    cout << "Command: ";
    getline(cin, line);
    fflush(stdin);
    return !line.empty();
}

void display(uint16_t set) {
    uint16_t mask = 1 << 15; // 32678
    while (mask > 0) {
        if(mask & set)
            cout << 1;
        else
            cout << 0;

        mask >>= 1;
    }
    cout << endl;
}

void process(string line, uint16_t &set) {
    try {
        set = stoi(line);      // todo: input validation, should be less than uint16_t max
    } catch (...) {
        cout << "Invalid input found\n";
        return;
    }

    set = ~set;
    cout << "Compliment: ";
    display(set);
}

void loadCommands(map<string, int> &commands) {
    commands["LOAD"] = 0;
    commands["SAVE"] = 1;
    commands["SET"] = 2;
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
 * @brief Processes commands for execution
 * @param line
 * @param commands
 *
 *
 */
void process(string line, const map<string, int> &commands) {
    string command, suffix;
    cout << "Processing...\n";
    trimLineAndStandardize(line);
    cout << line << endl;
    findCommand(line, command, suffix);
    cout << "Command: " << " Suffix: " << suffix << endl;
    executeCommand(command, suffix, commands);
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
void executeCommand(const string &command, const string &suffix, const map<string, int> &commands) {
    int whatToDo;
    if (commands.count(command))
        whatToDo = commands.at(command);
    else
        whatToDo = 99;

    switch(whatToDo) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            cout << "Invalid command!\n";
    }

}


