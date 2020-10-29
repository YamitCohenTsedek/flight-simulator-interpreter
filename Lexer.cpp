
#include "Lexer.h"

// Split the string that contains the whole script into strings that should be interpreted. 
vector<string> Lexer::spiltInfoToStrings(string info) {
    string currentString = "";
    vector<string> strings;
    bool isNumber = false;
    for (int i = 0; i<= info.length(); i++) {
        // Copy the character to currentString if it is a letter or a digit or '.'
        if (isalpha(info[i]) != 0 || isdigit(info[i]) != 0 || info[i] == '.') {
            currentString += info[i];
        }
        // Else - it is another character - that is the end of the current string.
        else {
            // Add currentString to the strings if it is not an empty word.
            if (currentString != "") {
                strings.push_back(currentString);
                currentString = "";
            }
            // If it is not the last character of the string:
            if (i != info.length()) {
                if (info[i] == ' ' || info[i] == '\t') {
                    continue;
                } else if (info[i] == '"') {
                    strings.push_back("\"");
                    i++;
                    while (info[i] != '"') {
                        currentString += info[i];
                        i++;
                    }
                    strings.push_back(currentString);
                    currentString = "";
                    strings.push_back("\"");
                    
                } else {
                    string sign;
                    sign += info[i];
                    strings.push_back(sign);
                }
            }
        }
    }
    if (strings[strings.size() - 1] != "\n") {
        strings.push_back("\n");
    }
    return strings;
}

// Read the script from the specified file.
vector<string> Lexer::readFromFile(string filename) {
    fstream file;
    file.open(filename);
    ifstream fromFile(filename);
    string line = "";
    string stringFromFile ="";
    if (fromFile.is_open()) {
        while (getline(fromFile, line)) {
            stringFromFile += line + "\n";
        }
    }
    else {
        throw std::invalid_argument("Error while opening the file.");
    }
    file.close();
    return spiltInfoToStrings(stringFromFile);
}