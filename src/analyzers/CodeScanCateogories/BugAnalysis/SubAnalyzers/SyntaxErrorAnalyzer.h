#ifndef SYNTAX_ERROR_ANALYZER_H
#define SYNTAX_ERROR_ANALYZER_H

#include <vector>
#include "../../../Analyzer.h"
#include "../../../../shared/AnalyzerTypes.h"

class SyntaxErrorAnalyzer : public Analyzer {   

private:
    
    void checkMissingSemicolons(const std::string& code, std::vector<Bug>& bugs);
    void checkUndefinedVariables(const std::string& code, std::vector<Bug>& errors);
    void checkMismatchedBrackets(const std::string& code, std::vector<Bug>& errors);
    void checkTypeMismatches(const std::string& code, std::vector<Bug>& errors);

    // TODO 
    // void checkUnusedVariables(const std::string& code, std::vector<Bug>& bugs);
    // void checkUnreachableCode(const std::string& code, std::vector<Bug>& bugs);
    // void checkDeadCode(const std::string& code, std::vector<Bug>& bugs);
    // void checkResourceLeaks(const std::string& code, std::vector<Bug>& bugs);
    // void checkNullPointerDereferences(const std::string& code, std::vector<Bug>& bugs);
    // void checkMemoryLeaks(const std::string& code, std::vector<Bug>& bugs);
    // void checkInfiniteLoops(const std::string& code, std::vector<Bug>& bugs);
    // void checkDivisionByZero(const std::string& code, std::vector<Bug>& bugs);
    // void checkUninitializedVariables(const std::string& code, std::vector<Bug>& bugs);
    // void checkConcurrencyIssues(const std::string& code, std::vector<Bug>& bugs);
    // void checkDeprecatedFunctions(const std::string& code, std::vector<Bug>& bugs);
    // void checkCodeDuplication(const std::string& code, std::vector<Bug>& bugs);
    // void checkSecurityVulnerabilities(const std::string& code, std::vector<Bug>& bugs);
    // void checkSecurityVulnerabilities(const std::string& code, std::vector<Bug>& bugs);
    // void checkPerformanceIssues(const std::string& code, std::vector<Bug>& bugs);
    // void checkNamingConventions(const std::string& code, std::vector<Bug>& bugs);
    // void checkMagicNumbers(const std::string& code, std::vector<Bug>& bugs);
    // void checkCodeComplexity(const std::string& code, std::vector<Bug>& bugs);
    // void checkExceptionHandling(const std::string& code, std::vector<Bug>& bugs);
    // void checkCodeStyleViolations(const std::string& code, std::vector<Bug>& bugs);
    // void checkAPIMisuse(const std::string& code, std::vector<Bug>& bugs);

    // Report errors
    void reportErrors();

    // Store errors
    std::vector<std::string> errorMessages;
    std::vector<std::string> tokens;

public:

    SyntaxErrorAnalyzer();

    std::vector<Bug> analyze(const std::string& code) override;

    // Return the sub-analyzer type
    BugScanAnalyzerType getSubType() const {
        return BugScanAnalyzerType::SyntaxError;
    }

    // Return high-level type (still required for base compatibility)
    CodeScanCategoriesType getType() const override {
        return CodeScanCategoriesType::BugDetection;
    }

    ~SyntaxErrorAnalyzer();
};

#endif // SYNTAX_ERROR_ANALYZER_H
