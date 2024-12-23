#include "AnalysisManager.h"
#include "../analyzers/Analyzer.h"
#include <iostream>

void AnalysisManager::registerAnalyzer(std::unique_ptr<Analyzer> analyzer) {
    analyzers.push_back(std::move(analyzer));
}

void AnalysisManager::analyzeCode(const std::string& code) {
    for (const auto& analyzer : analyzers) {
        auto bugs = analyzer->analyze(code);

        for (const auto& bug : bugs) {
            std::cout << "Bug: " << bug.description
                      << ", Line: " << bug.lineNumber << std::endl;
        }
    }
}
