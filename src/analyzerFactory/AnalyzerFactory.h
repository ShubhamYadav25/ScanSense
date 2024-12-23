#ifndef ANALYZER_FACTORY_H
#define ANALYZER_FACTORY_H

#include "shared/AnalyzerTypes.h"
#include <memory>
#include "analyzers/CodeScanCateogories/BugAnalysis/BugAnalyzer.h"
#include "analyzers/CodeScanCateogories/BugAnalysis/SubAnalyzers/SyntaxErrorAnalyzer.h"
#include "analyzers/CodeScanCateogories/SecurityAnalysis/SecurityAnalyzer.h"
#include <stdexcept>

class AnalyzerFactory {
public:
    // Factory method to create high-level analyzers
    static std::unique_ptr<Analyzer> createAnalyzer(CodeScanCategoriesType type) {
        switch (type) {
            case CodeScanCategoriesType::BugDetection:
                return std::make_unique<BugDetectionAnalyzer>();
            case CodeScanCategoriesType::Security:
                return std::make_unique<SecurityAnalyzer>();
            default:
                throw std::invalid_argument("Unknown high-level analyzer type.");
        }
    }

    // Factory method to create sub-analyzers for BugDetection
    static std::unique_ptr<Analyzer> createBugSubAnalyzer(BugScanAnalyzerType type) {
        switch (type) {
            case BugScanAnalyzerType::SyntaxError:
                return std::make_unique<SyntaxErrorAnalyzer>();
            case BugScanAnalyzerType::LogicalBug:
                    throw std::logic_error("PerformanceIssueAnalyzer not implemented yet.");
            case BugScanAnalyzerType::PerformanceIssue:
                // Return your PerformanceIssueAnalyzer here
                throw std::logic_error("PerformanceIssueAnalyzer not implemented yet.");
            default:
                throw std::invalid_argument("Unknown bug sub-analyzer type.");
        }
    }
};

#endif // ANALYZER_FACTORY_H
