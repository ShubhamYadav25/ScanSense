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
    return bugs;
}

void LogicalErrorAnalyzer::checkIncorrectLoopConditions(const std::string &code, std::vector<Bug>& bugs)
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