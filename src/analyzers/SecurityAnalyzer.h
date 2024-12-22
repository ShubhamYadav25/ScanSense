#ifndef SECURITY_ANALYZER_H
#define SECURITY_ANALYZER_H

#include "Analyzer.h"
#include <iostream>

class SecurityAnalyzer : public Analyzer {
public:
    void analyze(const std::string& code) override {
        std::cout << "SecurityAnalyzer: Analyzing for security issues in the code.\n";
    }
};

#endif // SECURITY_ANALYZER_H
