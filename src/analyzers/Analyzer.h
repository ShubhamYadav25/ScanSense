#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include "../shared/Bug.h"
#include "../shared/AnalyzerTypes.h"
#include <vector>
using namespace std;

// Base class for all analyzers
class Analyzer {
public:
    virtual ~Analyzer() = default;

    // Perform analysis on the given code
    virtual vector<Bug> analyze(const string& code) = 0;

    // Return the type of analyzer
    virtual CodeScanCategoriesType getType() const = 0;
};

#endif
