#include "SyntaxErrorAnalyzer.h"
#include "../../../../shared/Bug.h"

#include <vector>

std::vector<Bug> SyntaxErrorAnalyzer::analyze(const std::string& code) {
    std::vector<Bug> bugs;

    // Simple example: Detect missing semicolons
    if (code.find(';') == std::string::npos) {
        // bugs.push_back(Bug("Missing semicolon", 1));
    }

    return bugs;
}
