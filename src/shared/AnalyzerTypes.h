#ifndef ANALYZER_TYPES_H
#define ANALYZER_TYPES_H

// Enum for high-level code scan categories
enum class CodeScanCategoriesType {
    BugDetection,
    Security,
    Reliability,
    Maintainability,
    Adaptability,
    Intentionality,
    Responsibility,
    Consistency
};

// Enum for sub-analyzers under Bug Detection
enum class BugScanAnalyzerType {
    SyntaxError,
    LogicalBug,
    PerformanceIssue,
    BestPracticeViolation,
    SecurityVulnerability,
    CommonCodingMistake
};

#endif // ANALYZER_TYPES_H
