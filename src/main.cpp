#include "analysisManager/AnalysisManager.h"
#include "analyzerFactory/AnalyzerFactory.h"
#include "shared/AnalyzerTypes.h"
#include <iostream>

int main() {
    std::string sampleCode = R"(
        int main() {
            int x = 5
            return 0;
        }
    )";

    // Create BugDetectionAnalyzer using the factory
    auto bugDetectionAnalyzer = AnalyzerFactory::createAnalyzer(CodeScanCategoriesType::BugDetection);

    // Add sub-analyzers dynamically using the factory
    auto bugDetection = dynamic_cast<BugDetectionAnalyzer*>(bugDetectionAnalyzer.get());
    if (bugDetection) {
        bugDetection->addSubAnalyzer(BugScanAnalyzerType::SyntaxError, AnalyzerFactory::createBugSubAnalyzer(BugScanAnalyzerType::SyntaxError));
        
        // bugDetection->addSubAnalyzer(BugScanAnalyzerType::LogicalBug, AnalyzerFactory::createBugSubAnalyzer(BugScanAnalyzerType::LogicalBug));
    }

    // Create AnalysisManager and add analyzers
    AnalysisManager analysisManager;
    analysisManager.registerAnalyzer(std::move(bugDetectionAnalyzer));

    // Analyze the code and display bugs
    analysisManager.analyzeCode(sampleCode);
    
    return 0;
}
