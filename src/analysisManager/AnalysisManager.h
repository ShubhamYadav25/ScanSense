#ifndef ANALYSIS_MANAGER_H
#define ANALYSIS_MANAGER_H

#include "../analyzers/Analyzer.h"
#include <vector>
#include <memory>

class AnalysisManager {
private:
    std::vector<std::unique_ptr<Analyzer>> analyzers;

public:
    void registerAnalyzer(std::unique_ptr<Analyzer> analyzer);
    void analyzeCode(const std::string& code);
};

#endif // ANALYSIS_MANAGER_H
