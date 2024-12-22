#ifndef BUG_ANALYZER_H
#define BUG_ANALYZER_H

#include "Analyzer.h"
#include <iostream>

class BugAnalyzer : public Analyzer {
public:
    void analyze(const std::string& code) override {
        std::cout << "BugAnalyzer: Analyzing for bugs in the code.\n";
    }
};

#endif // BUG_ANALYZER_H
