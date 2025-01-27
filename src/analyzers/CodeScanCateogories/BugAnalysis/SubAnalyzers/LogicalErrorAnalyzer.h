#ifndef LOGICAL_ERROR_ANALYZER_H
#define LOGICAL_ERROR_ANALYZER_H

#include <vector>
#include "../../../Analyzer.h"
#include "../../../../shared/AnalyzerTypes.h"

class LogicalErrorAnalyzer : public Analyzer {   

private:
    
    // 1. Incorrect Loop Conditions  && Off-by-One Errors
    void checkIncorrectLoopConditions(const std::string& code, std::vector<Bug>& bugs);

    // 2. Incorrect Boolean Logic
    void checkIncorrectBooleanLogic(const std::string& code, std::vector<Bug>& bugs);

    // 3. Incorrect Comparison Operators
    void checkIncorrectComparisonOperators(const std::string& code, std::vector<Bug>& bugs);

    // 4. Incorrect Order of Operations
    void checkIncorrectOrderOfOperations(const std::string& code, std::vector<Bug>& bugs);

    // 5. Incorrect Loop Variable Updates
    void checkIncorrectLoopVariableUpdates(const std::string& code, std::vector<Bug>& bugs);

    // 6. Incorrect Switch-Case Logic
    void checkIncorrectSwitchCaseLogic(const std::string& code, std::vector<Bug>& bugs);

    // 7. Incorrect Function Return Logic
    void checkIncorrectFunctionReturnLogic(const std::string& code, std::vector<Bug>& bugs);

    // 8. Incorrect Recursion Logic
    void checkIncorrectRecursionLogic(const std::string& code, std::vector<Bug>& bugs);

    // 9. Incorrect Handling of Edge Cases
    void checkIncorrectEdgeCaseHandling(const std::string& code, std::vector<Bug>& bugs);

    // Report errors
    void reportErrors();

    // Store errors
    std::vector<std::string> errorMessages;
    std::vector<std::string> tokens;

public:

    LogicalErrorAnalyzer();

    std::vector<Bug> analyze(const std::string& code) override;

    // Return the sub-analyzer type
    BugScanAnalyzerType getSubType() const {
        return BugScanAnalyzerType::LogicalError;
    }

    // Return high-level type (still required for base compatibility)
    CodeScanCategoriesType getType() const override {
        return CodeScanCategoriesType::BugDetection;
    }

    ~LogicalErrorAnalyzer();
};

#endif // LOGICAL_ERROR_ANALYZER_H
