#ifndef ANALYZER_FACTORY_H
#define ANALYZER_FACTORY_H

#include "analyzers/BugAnalyzer.h"
#include "analyzers/SecurityAnalyzer.h"
#include "shared/AnalyzerTypes.h"
#include <memory>

class AnalyzerFactory {
public:
    static std::unique_ptr<Analyzer> createAnalyzer(AnalyzerType type) {
        switch (type) {
            case AnalyzerType::Bug:
                return std::make_unique<BugAnalyzer>();
            case AnalyzerType::Security:
                return std::make_unique<SecurityAnalyzer>();
            default:
                throw std::invalid_argument("Unknown analyzer type.");
        }
    }
};

#endif // ANALYZER_FACTORY_H
