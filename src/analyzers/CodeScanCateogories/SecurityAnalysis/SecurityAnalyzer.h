#ifndef SECURITY_ANALYZER_H
#define SECURITY_ANALYZER_H

#include "../../Analyzer.h"
#include "../../../shared/AnalyzerTypes.h"
#include <iostream>

class SecurityAnalyzer : public Analyzer {
public:
       std::vector<Bug> analyze(const std::string& code) override;

       virtual CodeScanCategoriesType getType() const {
           return CodeScanCategoriesType::Security;
       }
};

#endif // SECURITY_ANALYZER_H
