#include "SharedClass.h"
#include <iostream>

// Private method implementation: Check if a word is a C++ keyword
bool SharedClass::isKeyword(const std::string& word) {
    static const std::vector<std::string> keywords = {
        "int", "double", "float", "char", "bool", "if", "else", "while", "for", "return"
    };
    return std::find(keywords.begin(), keywords.end(), word) != keywords.end();
}

// Private method implementation: Check if a word is a number
bool SharedClass::isNumber(const std::string& word) {
    return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
}