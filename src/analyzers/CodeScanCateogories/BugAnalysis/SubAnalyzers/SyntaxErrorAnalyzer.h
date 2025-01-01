#ifndef SYNTAX_ERROR_ANALYZER_H
#define SYNTAX_ERROR_ANALYZER_H

#include <vector>
#include "../../../Analyzer.h"
#include "../../../../shared/AnalyzerTypes.h"

class SyntaxErrorAnalyzer : public Analyzer {   

private:
    // Helper method to tokenize the code
    void tokenizeCode(const std::string& code);

    // Helper methods for syntax checks
    void checkMissingSemicolons(const std::string& code, std::vector<Bug>& bugs);
    void checkUndefinedVariables(const std::string& code);
    void checkMismatchedBrackets(const std::string& code);
    void checkTypeMismatches(const std::string& code);

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
