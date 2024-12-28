#include "SyntaxErrorAnalyzer.h"
#include "../../../../shared/Bug.h"

#include <vector>
#include <iostream>
#include <regex>

SyntaxErrorAnalyzer::SyntaxErrorAnalyzer() {
    // Initialization 
}

std::vector<Bug> SyntaxErrorAnalyzer::analyze(const std::string& code) {
    std::vector<Bug> bugs;

   // Tokenize the code first
    tokenizeCode(code);

    // Perform the syntax checks
    checkMissingSemicolons(code);
    checkUndefinedVariables(code);
    checkMismatchedBrackets(code);
    checkTypeMismatches(code);

    // Report errors if any
    reportErrors();
    
   
    return bugs;
}

void SyntaxErrorAnalyzer::tokenizeCode(const std::string& code) {
    std::regex tokenPattern(R"(\b\w+\b|[{}();,+\-*/=<>!&|^%])");
    std::sregex_iterator begin(code.begin(), code.end(), tokenPattern);
    std::sregex_iterator end;

    tokens.clear();
    for (auto it = begin; it != end; ++it) {
        tokens.push_back(it->str());
    }
}

void SyntaxErrorAnalyzer::checkMissingSemicolons(const std::string& code) {
    size_t pos = 0;
    while ((pos = code.find(";", pos)) != std::string::npos) {
        size_t prevNonSpace = pos - 1;
        while (prevNonSpace >= 0 && std::isspace(code[prevNonSpace])) {
            --prevNonSpace;
        }

        if (prevNonSpace < 0 || code[prevNonSpace] != '}') {
            errorMessages.push_back("Error: Missing semicolon before line " + std::to_string(pos));
        }
        pos += 1;
    }
}

void SyntaxErrorAnalyzer::checkUndefinedVariables(const std::string& code) {
    std::regex variablePattern(R"(\b(int|float|char|double|std::string)\s+(\w+))");
    std::sregex_iterator begin(code.begin(), code.end(), variablePattern);
    std::sregex_iterator end;

    std::vector<std::string> declaredVariables;

    for (auto it = begin; it != end; ++it) {
        declaredVariables.push_back(it->str(2));  // Store the variable name
    }

    std::regex usagePattern(R"(\b(\w+)\b)");
    begin = std::sregex_iterator(code.begin(), code.end(), usagePattern);

    for (auto it = begin; it != end; ++it) {
        std::string variable = it->str();
        if (std::find(declaredVariables.begin(), declaredVariables.end(), variable) == declaredVariables.end()) {
            errorMessages.push_back("Error: Undefined variable '" + variable + "' used.");
        }
    }
}

void SyntaxErrorAnalyzer::checkMismatchedBrackets(const std::string& code) {
    std::vector<char> stack;

    for (char c : code) {
        if (c == '(' || c == '{' || c == '[') {
            stack.push_back(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (stack.empty()) {
                errorMessages.push_back("Error: Mismatched closing bracket at line " + std::to_string(code.find(c)));
            } else {
                char opening = stack.back();
                if ((c == ')' && opening == '(') ||
                    (c == '}' && opening == '{') ||
                    (c == ']' && opening == '[')) {
                    stack.pop_back();
                } else {
                    errorMessages.push_back("Error: Mismatched closing bracket at line " + std::to_string(code.find(c)));
                }
            }
        }
    }

    if (!stack.empty()) {
        errorMessages.push_back("Error: Unmatched opening bracket(s).");
    }
}

void SyntaxErrorAnalyzer::checkTypeMismatches(const std::string& code) {
    std::regex assignmentPattern(R"((\w+)\s*=\s*(\w+))");
    std::sregex_iterator begin(code.begin(), code.end(), assignmentPattern);
    std::sregex_iterator end;

    for (auto it = begin; it != end; ++it) {
        std::string lhs = it->str(1); 
        std::string rhs = it->str(2);  

        if (lhs == "int" && rhs == "string") {
            errorMessages.push_back("Error: Type mismatch between left side and right side in assignment.");
        }
    }
}

void SyntaxErrorAnalyzer::reportErrors() {
    if (errorMessages.empty()) {
        std::cout << "No syntax errors found." << std::endl;
    } else {
        for (const auto& error : errorMessages) {
            std::cout << error << std::endl;
        }
    }
}

SyntaxErrorAnalyzer::~SyntaxErrorAnalyzer() {
    // Cleanup 
}
