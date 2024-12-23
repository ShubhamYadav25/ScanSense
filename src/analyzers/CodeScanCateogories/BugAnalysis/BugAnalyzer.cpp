#include "BugAnalyzer.h"
#include "../../Analyzer.h"

void BugDetectionAnalyzer::addSubAnalyzer(BugScanAnalyzerType type, std::unique_ptr<Analyzer> analyzer) {
    subAnalyzers[type] = std::move(analyzer);
}

std::vector<Bug> BugDetectionAnalyzer::analyze(const std::string& code) {
    bugs.clear();

    for (const auto& [type, analyzer] : subAnalyzers) {
        auto detectedBugs = analyzer->analyze(code);
        bugs.insert(bugs.end(), detectedBugs.begin(), detectedBugs.end());
    }

    return bugs;
}
