#ifndef SYNTAX_ERROR_ANALYZER_H
#define SYNTAX_ERROR_ANALYZER_H

#include <vector>
#include "../../../Analyzer.h"
#include "../../../../shared/AnalyzerTypes.h"

class SyntaxErrorAnalyzer : public Analyzer {
public:
    std::vector<Bug> analyze(const std::string& code) override;

    // Return the sub-analyzer type
    BugScanAnalyzerType getSubType() const {
        return BugScanAnalyzerType::SyntaxError;
    }

    // Return high-level type (still required for base compatibility)
    CodeScanCategoriesType getType() const override {
        return CodeScanCategoriesType::BugDetection;
    }
};

#endif // SYNTAX_ERROR_ANALYZER_H
