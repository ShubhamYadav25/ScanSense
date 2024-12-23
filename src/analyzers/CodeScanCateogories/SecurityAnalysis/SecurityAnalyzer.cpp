#include "SecurityAnalyzer.h"
#include <vector>
#include "shared/Bug.h"

std::vector<Bug> SecurityAnalyzer::analyze(const std::string& code) {
    std::vector<Bug> bugs;

    // Example: Check for hardcoded credentials
    if (code.find("password") != std::string::npos) {
        bugs.push_back({"Hardcoded password found", 0});
    }

    return bugs;
}
