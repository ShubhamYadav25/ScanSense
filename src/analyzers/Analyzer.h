#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>

class Analyzer {
public:
    virtual ~Analyzer() = default;
    virtual void analyze(const std::string& code) = 0;
};

#endif
