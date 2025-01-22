#ifndef SHAREDCLASS_H
#define SHAREDCLASS_H

#include <string>
#include <vector>
#include <algorithm> // for std::find, std::all_of
#include <cctype>    // for ::isdigit

class SharedClass {
public:
    // Private method to check if a word is a C++ keyword
    bool static isKeyword(const std::string& word);

    // Private method to check if a word is a number
    bool static isNumber(const std::string& word);
};

#endif 