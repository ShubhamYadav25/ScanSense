#include "SyntaxErrorAnalyzer.h"
#include "../../../../shared/Bug.h"
#include "../../../../shared/SharedClass.h"

#include <vector>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>
#include <unordered_map>

SyntaxErrorAnalyzer::SyntaxErrorAnalyzer()
{
    // Initialization
}

std::vector<Bug> SyntaxErrorAnalyzer::analyze(const std::string &code)
{
    std::vector<Bug> bugs;

    // Perform the syntax checks
    checkMissingSemicolons(code, bugs);
    checkUndefinedVariables(code, bugs);
    checkMismatchedBrackets(code, bugs);
    checkTypeMismatches(code, bugs);

    // Report errors if any
    reportErrors();

    return bugs;
}

void SyntaxErrorAnalyzer::checkMissingSemicolons(const std::string &code,  std::vector<Bug>& errors)
{
    // get c++ code line by line
    std::istringstream stream(code);
    std::string line;

    int lineNumber = 0;

    while (std::getline(stream, line))
    {
        lineNumber++;

        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        // Skip preprocessor directives   ex: #include 
        if (line[0] == '#')
        {
            continue;
        }

        // Skip single-line comments      ex:  comments (//.....)
        if (line.find("//") != std::string::npos)
        {
            line = line.substr(0, line.find("//"));
        }

        /***
         * Skip lines ending with {, }, or : as they don't need semicolons   
         * ex:  func() { ......
         * ex :  ....}
         */
        char lastChar = line.back();
        while (isspace(lastChar) && line.length() > 1)
        {
            line.pop_back();
            lastChar = line.back();
        }
        if (lastChar == '{' || lastChar == '}' || lastChar == ':')
        {
            continue;
        }

        // Skip function declarations and control statements
        if (line.find("if") == 0 || line.find("for") == 0 ||
            line.find("while") == 0 || line.find("else") == 0)
        {
            continue;
        }

        // Check if line ends with semicolon
        if (lastChar != ';')
        {
            errors.push_back(
                Bug{
                    "Missing semicolon at the end of line " + std::to_string(lineNumber),
                    lineNumber
            });
        }
    }
}

void SyntaxErrorAnalyzer::checkUndefinedVariables(const std::string &code, std::vector<Bug>& errors)
{
    std::map<std::string, int> declaredVariables; // Maps variable name to line number where it was declared
    std::istringstream stream(code);
    std::string line;
    int lineNumber = 0;

    // Regex to match variable declarations (simplified for demonstration)
    std::regex declarationRegex(R"((int|double|float|char|bool)\s+(\w+)\s*(?:=\s*[^;]+)?;)");
    // Regex to match variable usages
    std::regex usageRegex(R"(\b(\w+)\b)");

    while (std::getline(stream, line)) {
        lineNumber++;
        std::smatch matches;

        // Check for variable declarations
        if (std::regex_search(line, matches, declarationRegex)) {
            std::string variableName = matches[2];
            declaredVariables[variableName] = lineNumber;
        }

        // Check for variable usages
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), usageRegex);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string variableName = match.str();

            // Skip keywords and numbers
            if (SharedClass::isKeyword(variableName) || SharedClass::isNumber(variableName)) {
                continue;
            }

            // Check if the variable is declared
            if (declaredVariables.find(variableName) == declaredVariables.end()) {
                Bug bug;
                bug.lineNumber = lineNumber;
                bug.description = "Undefined variable '" + variableName + "'";
                errors.push_back(bug);
            }
        }
    }
}

void SyntaxErrorAnalyzer::checkMismatchedBrackets(const std::string &code, std::vector<Bug>& errors)
{
    // Stores the bracket and its line number
    std::stack<std::pair<char, int>> bracketStack; 
    std::unordered_map<char, char> bracketPairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    std::istringstream stream(code);
    std::string line;
    int lineNumber = 0;

    while (std::getline(stream, line)) {
        lineNumber++;
        for (size_t i = 0; i < line.length(); i++) {
            char ch = line[i];

            // If it's an opening bracket, push onto the stack with its line number
            if (ch == '(' || ch == '[' || ch == '{') {
                bracketStack.push({ch, lineNumber});
            }
            // If it's a closing bracket
            else if (ch == ')' || ch == ']' || ch == '}') {
                // Check if the stack is empty or the top doesn't match
                if (bracketStack.empty() || bracketStack.top().first != bracketPairs[ch]) {
                    Bug bug;
                    bug.lineNumber = lineNumber;
                    bug.description = "Mismatched closing bracket '" + std::string(1, ch) + "'";
                    errors.push_back(bug);
                } else {
                    // Pop the matching opening bracket
                    bracketStack.pop();
                }
            }
        }
    }

    // Check for unmatched opening brackets
    while (!bracketStack.empty()) {
        Bug bug;
        bug.lineNumber = bracketStack.top().second;
        bug.description = "Missing closing bracket for '" + std::string(1, bracketStack.top().first) + "'";
        errors.push_back(bug);
        bracketStack.pop();
    }
}

void SyntaxErrorAnalyzer::checkTypeMismatches(const std::string &code, std::vector<Bug>& errors)
{
    // Maps variable names to their types
    // { x, int }
    std::map<std::string, std::string> variableTypes; 
    std::istringstream stream(code);
    std::string line;
    int lineNumber = 0;

    // Regex to match variable declarations (e.g., "int x;")
    std::regex declarationRegex(R"((int|double|float|char|bool|std::string)\s+(\w+)\s*(?:=\s*([^;]+))?;)");

    // Regex to match assignments (e.g., "x = 10;")
    std::regex assignmentRegex(R"((\w+)\s*=\s*([^;]+);)");

    while (std::getline(stream, line)) {
        lineNumber++;
        std::smatch matches;

        // Check for variable declarations
        if (std::regex_search(line, matches, declarationRegex)) {
            std::string type = matches[1];
            std::string variableName = matches[2];
            variableTypes[variableName] = type;

            // Check for initialization (e.g., "int x = 10;")
            // if we get matches[3].matched true it means variable is intialized at the time of declaration
            if (matches[3].matched) {
                std::string value = matches[3];
                // Simple type checking for initialization
                if ((type == "int" && !std::regex_match(value, std::regex(R"(\d+)"))) ||
                    (type == "double" && !std::regex_match(value, std::regex(R"(\d+\.\d+)"))) ||
                    (type == "std::string" && !std::regex_match(value, std::regex(R"(\".*\")")))) {
                    Bug bug;
                    bug.lineNumber = lineNumber;
                    bug.description = "Type mismatch: Cannot initialize '" + variableName + "' of type '" + type + "' with value '" + value + "'";
                    errors.push_back(bug);
                }
            }
        }

        // Check for assignments
        if (std::regex_search(line, matches, assignmentRegex)) {
            std::string variableName = matches[1];
            std::string value = matches[2];

            if (variableTypes.find(variableName) != variableTypes.end()) {
                std::string type = variableTypes[variableName];

                // Simple type checking for assignments
                if ((type == "int" && !std::regex_match(value, std::regex(R"(\d+)"))) ||
                    (type == "double" && !std::regex_match(value, std::regex(R"(\d+\.\d+)"))) ||
                    (type == "std::string" && !std::regex_match(value, std::regex(R"(\".*\")")))) {
                    Bug bug;
                    bug.lineNumber = lineNumber;
                    bug.description = "Type mismatch: Cannot assign value '" + value + "' to variable '" + variableName + "' of type '" + type + "'";
                    errors.push_back(bug);
                }
            }
        }
    }
}

void SyntaxErrorAnalyzer::reportErrors()
{
    if (errorMessages.empty())
    {
        std::cout << "No syntax errors found." << std::endl;
    }
    else
    {
        for (const auto &error : errorMessages)
        {
            std::cout << error << std::endl;
        }
    }
}

SyntaxErrorAnalyzer::~SyntaxErrorAnalyzer()
{
    // Cleanup
}

/***
 * 
 * Healper methods
 * 
 */
