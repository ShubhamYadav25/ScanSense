#ifndef BUG_DETECTION_ANALYZER_H
#define BUG_DETECTION_ANALYZER_H

#include "../../Analyzer.h"
#include "../../../shared/AnalyzerTypes.h"
#include <vector>
#include <memory>
#include <unordered_map>

class BugDetectionAnalyzer : public Analyzer {
private:
    std::unordered_map<BugScanAnalyzerType, std::unique_ptr<Analyzer>> subAnalyzers;
    std::vector<Bug> bugs;

public:
    void addSubAnalyzer(BugScanAnalyzerType type, std::unique_ptr<Analyzer> analyzer);

    std::vector<Bug> analyze(const std::string& code) override;

    CodeScanCategoriesType getType() const override {
        return CodeScanCategoriesType::BugDetection;
    }
};

#endif // BUG_DETECTION_ANALYZER_H
