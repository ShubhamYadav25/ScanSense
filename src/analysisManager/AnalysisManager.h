#ifndef ANALYSIS_MANAGER_H
#define ANALYSIS_MANAGER_H

#include "../analyzers/Analyzer.h"
#include <vector>
#include <memory>

class AnalysisManager {
private:
    std::vector<std::unique_ptr<Analyzer>> analyzers;

public:
    void addAnalyzer(std::unique_ptr<Analyzer> analyzer) {
        analyzers.push_back(std::move(analyzer));
    }

    void analyze(const std::string& code) {
        for (const auto& analyzer : analyzers) {
            analyzer->analyze(code);
        }
    }
};

#endif // ANALYSIS_MANAGER_H
