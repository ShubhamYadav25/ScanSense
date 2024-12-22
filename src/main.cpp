#include <iostream>
 
#include "analysisManager/AnalysisManager.h"
#include "analyzerFactory/AnalyzerFactory.h"

int main() {
    AnalysisManager manager;

    // Create analyzers using the factory
    auto bugAnalyzer = AnalyzerFactory::createAnalyzer(AnalyzerType::Bug);
    auto securityAnalyzer = AnalyzerFactory::createAnalyzer(AnalyzerType::Security);

    // Add analyzers to the manager
    manager.addAnalyzer(std::move(bugAnalyzer));
    manager.addAnalyzer(std::move(securityAnalyzer));

    // Analyze the given code
    std::string code = "int main() { return 0; }";
    manager.analyze(code);

    return 0;
}
