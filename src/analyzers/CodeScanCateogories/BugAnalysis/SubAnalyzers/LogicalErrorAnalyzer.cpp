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

std::vector<Bug> LogicalErrorAnalyzer::analyze(const std::string &code){

    std::vector<Bug> bugs;
    checkIncorrectLoopConditions(code, bugs);


}

void checkIncorrectLoopConditions(const std::string& code, std::vector<Bug>& bugs){

}