#include "LogicalErrorAnalyzer.h"
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

/***
 * Helper method
 */
// Utility function to split code into lines
std::vector<std::string> splitIntoLines(const std::string &code)
{
    std::vector<std::string> lines;
    size_t start = 0;
    size_t end = code.find('\n');
    while (end != std::string::npos)
    {
        lines.push_back(code.substr(start, end - start));
        start = end + 1;
        end = code.find('\n', start);
    }
    lines.push_back(code.substr(start));
    return lines;
}

// Utility function to detect patterns in code
bool containsPattern(const std::string &line, const std::regex &pattern)
{
    return std::regex_search(line, pattern);
}

LogicalErrorAnalyzer::LogicalErrorAnalyzer()
{
    // Initialization
}

LogicalErrorAnalyzer::~LogicalErrorAnalyzer()
{
    // Cleanup
}

std::vector<Bug> LogicalErrorAnalyzer::analyze(const std::string &code)
{

    std::vector<Bug> bugs;
    checkIncorrectLoopConditions(code, bugs);
    checkIncorrectBooleanLogic(code, bugs);
    checkIncorrectBooleanLogic(code, bugs);
    checkIncorrectOrderOfOperations(code, bugs);
    checkIncorrectOrderOfOperations(code, bugs);
    checkIncorrectSwitchCaseLogic(code, bugs);
    checkIncorrectLoopVariableUpdates(code, bugs);
    checkIncorrectSwitchCaseLogic(code, bugs);
    checkIncorrectFunctionReturnLogic(code, bugs);
    checkIncorrectRecursionLogic(code, bugs);
    checkIncorrectEdgeCaseHandling(code, bugs);

    return bugs;
}

void LogicalErrorAnalyzer::checkIncorrectLoopConditions(const std::string &code, std::vector<Bug> &bugs)
{
    std::regex loopRegex(R"((for|while)\s*\(([^;]*);([^;]*);([^)]*)\)\s*\{)");
    std::smatch matches;
    std::string::const_iterator searchStart(code.cbegin());
    int lineNumber = 1;

    while (std::regex_search(searchStart, code.cend(), matches, loopRegex))
    {
        // for or while
        std::string loopType = matches[1];

        std::string initCondition = matches[2];
        std::string loopCondition = matches[3];
        std::string increment = matches[4];

        // Check for common issues in loop conditions
        if (loopCondition.empty())
        {
            bugs.push_back({"Empty loop condition in " + loopType + " loop", lineNumber});
        }
        else if (loopCondition == "true")
        {
            bugs.push_back({"Infinite loop detected: condition is always true", lineNumber});
        }
        else if (loopCondition.find("<=") != std::string::npos || loopCondition.find(">=") != std::string::npos)
        {
            // Check for potential off-by-one errors
            bugs.push_back({"Potential off-by-one error in loop condition", lineNumber});
        }

        // Update line number by counting newlines in the matched string
        lineNumber += std::count(matches[0].first, matches[0].second, '\n');

        // Move the search start to the end of the current match
        searchStart = matches.suffix().first;
    }
}

void LogicalErrorAnalyzer::checkIncorrectBooleanLogic(const std::string &code, std::vector<Bug> &bugs)
{

    /**
     * if (true) or if (false): Redundant conditions.
     * if (x == true) or if (x == false): Suspicious boolean expressions.
     * if (x = y): Potential typo (assignment instead of comparison).
     */
    std::vector<std::pair<std::regex, std::string>> patterns = {
        {std::regex(R"(\bif\s*\(\s*true\s*\))"), "Redundant condition: always true"},
        {std::regex(R"(\bif\s*\(\s*false\s*\))"), "Redundant condition: always false"},
        {std::regex(R"(\bif\s*\(\s*\w+\s*==\s*true\b)"), "Suspicious boolean expression: comparison with true"},
        {std::regex(R"(\bif\s*\(\s*\w+\s*==\s*false\b)"), "Suspicious boolean expression: comparison with false"},
        {std::regex(R"(\bif\s*\(\s*\w+\s*=\s*\w+\s*\))"), "Potential typo: assignment instead of comparison"}};

    int lineNumber = 1;
    std::istringstream codeStream(code);
    std::string line;

    // Iterate through each line of the code
    while (std::getline(codeStream, line))
    {
        for (const auto &pattern : patterns)
        {
            if (std::regex_search(line, pattern.first))
            {
                bugs.push_back({pattern.second, lineNumber});
            }
        }
        lineNumber++;
    }
}

void LogicalErrorAnalyzer::checkIncorrectComparisonOperators(const std::string &code, std::vector<Bug> &bugs)
{
    std::vector<std::pair<std::regex, std::string>> patterns = {
        {std::regex(R"(\b\w+\s*==\s*true\b)"), "Suspicious comparison: == with true"},
        {std::regex(R"(\b\w+\s*==\s*false\b)"), "Suspicious comparison: == with false"},
        {std::regex(R"(\b\w+\s*!=\s*true\b)"), "Suspicious comparison: != with true"},
        {std::regex(R"(\b\w+\s*!=\s*false\b)"), "Suspicious comparison: != with false"},
        {std::regex(R"(\b\w+\s*=\s*\w+\b)"), "Potential typo: = instead of =="}};

    int lineNumber = 1;
    std::istringstream codeStream(code);
    std::string line;

    // Iterate through each line of the code
    while (std::getline(codeStream, line))
    {
        for (const auto &pattern : patterns)
        {
            if (std::regex_search(line, pattern.first))
            {
                bugs.push_back({pattern.second, lineNumber});
            }
        }
        lineNumber++;
    }
}

void LogicalErrorAnalyzer::checkIncorrectOrderOfOperations(const std::string &code, std::vector<Bug> &bugs)
{

    /***
     * Arithmetic expressions: Matches expressions like a + b * c where parentheses might be missing.
     * Logical expressions: Matches expressions like x && y || z where parentheses might be missing.
     */

    std::vector<std::pair<std::regex, std::string>> patterns = {
        {std::regex(R"(\b\w+\s*[+\-*/]\s*\w+\s*[+\-*/]\s*\w+\b)"), "Potential issue: missing parentheses in arithmetic expression"},
        {std::regex(R"(\b\w+\s*&&\s*\w+\s*\|\|\s*\w+\b)"), "Potential issue: missing parentheses in logical expression"}};

    int lineNumber = 1;
    std::istringstream codeStream(code);
    std::string line;

    // Iterate through each line of the code
    while (std::getline(codeStream, line))
    {
        for (const auto &pattern : patterns)
        {
            if (std::regex_search(line, pattern.first))
            {
                bugs.push_back({pattern.second, lineNumber});
            }
        }
        lineNumber++;
    }
}

void LogicalErrorAnalyzer::checkIncorrectLoopVariableUpdates(const std::string &code, std::vector<Bug> &bugs)
{
    std::regex loopPattern(R"((for\s*\(.*;.*;.*\)|while\s*\(.*\)))");
    std::regex updatePattern(R"((\+\+|--|[+-]=))");
    auto lines = splitIntoLines(code);

    for (size_t i = 0; i < lines.size(); ++i)
    {
        if (containsPattern(lines[i], loopPattern) && !containsPattern(lines[i], updatePattern))
        {
            bugs.push_back({"Potential incorrect loop variable update", static_cast<int>(i + 1)});
        }
    }
}

void LogicalErrorAnalyzer::checkIncorrectSwitchCaseLogic(const std::string &code, std::vector<Bug> &bugs)
{
    std::regex switchPattern(R"(switch\s*\(.*\)\s*\{)");
    std::regex defaultPattern(R"(default\s*:)");
    auto lines = splitIntoLines(code);
    bool inSwitch = false;

    for (size_t i = 0; i < lines.size(); ++i)
    {
        if (containsPattern(lines[i], switchPattern))
        {
            inSwitch = true;
        }
        if (inSwitch && containsPattern(lines[i], defaultPattern))
        {
            inSwitch = false;
        }
        if (inSwitch && lines[i].find('}') != std::string::npos)
        {
            bugs.push_back({"Switch statement missing default case", static_cast<int>(i + 1)});
            inSwitch = false;
        }
    }
}

void LogicalErrorAnalyzer::checkIncorrectFunctionReturnLogic(const std::string &code, std::vector<Bug> &bugs)
{
    std::regex functionPattern(R"(\w+\s+\w+\s*\(.*\)\s*\{)");
    std::regex returnPattern(R"(return\s+[^;]+;)");
    auto lines = splitIntoLines(code);
    bool inFunction = false;
    bool hasReturn = false;

    for (size_t i = 0; i < lines.size(); ++i)
    {
        if (containsPattern(lines[i], functionPattern))
        {
            inFunction = true;
            hasReturn = false;
        }
        if (inFunction && containsPattern(lines[i], returnPattern))
        {
            hasReturn = true;
        }
        if (inFunction && lines[i].find('}') != std::string::npos)
        {
            if (!hasReturn)
            {
                bugs.push_back({"Function may not return a value on all paths", static_cast<int>(i + 1)});
            }
            inFunction = false;
        }
    }
}

void LogicalErrorAnalyzer::checkIncorrectRecursionLogic(const std::string &code, std::vector<Bug> &bugs)
{
    std::regex functionPattern(R"(\w+\s+\w+\s*\(.*\)\s*\{)");
    std::regex baseCasePattern(R"(if\s*\(.*\)\s*return)");
    auto lines = splitIntoLines(code);
    bool inFunction = false;
    bool hasBaseCase = false;

    for (size_t i = 0; i < lines.size(); ++i)
    {
        if (containsPattern(lines[i], functionPattern))
        {
            inFunction = true;
            hasBaseCase = false;
        }
        if (inFunction && containsPattern(lines[i], baseCasePattern))
        {
            hasBaseCase = true;
        }
        if (inFunction && lines[i].find('}') != std::string::npos)
        {
            if (!hasBaseCase)
            {
                bugs.push_back({"Recursive function may lack a base case", static_cast<int>(i + 1)});
            }
            inFunction = false;
        }
    }
}

void LogicalErrorAnalyzer::checkIncorrectEdgeCaseHandling(const std::string &code, std::vector<Bug> &bugs)
{
    std::regex edgeCasePattern(R"(if\s*\(\s*\w+\s*==\s*nullptr\s*\)|\s*if\s*\(\s*\w+\s*==\s*0\s*\))");
    auto lines = splitIntoLines(code);

    for (size_t i = 0; i < lines.size(); ++i)
    {
        if (!containsPattern(lines[i], edgeCasePattern))
        {
            bugs.push_back({"Potential missing edge case handling", static_cast<int>(i + 1)});
        }
    }
}

