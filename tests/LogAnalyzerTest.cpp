#include <gtest/gtest.h>

#include "LogAnalyzer.h"

TEST(LogAnalyzerTest, CountsLogLevels) {
    LogAnalyzer analyzer;

    analyzer.process({
        "2026-10-06 10:21:32",
        LogLevel::INFO,
        "User login successful"
    });

    analyzer.process({
        "2026-10-06 10:21:35",
        LogLevel::ERROR,
        "Database connection failed"
    });

    analyzer.process({
        "2026-10-06 10:21:37",
        LogLevel::WARN,
        "Retry attempt 2"
    });

    EXPECT_EQ(analyzer.getTotalCount(), 3);
    EXPECT_EQ(analyzer.getInfoCount(), 1);
    EXPECT_EQ(analyzer.getWarnCount(), 1);
    EXPECT_EQ(analyzer.getErrorCount(), 1);
}

TEST(LogAnalyzerTest, CountsRepeatedErrors) {
    LogAnalyzer analyzer;

    analyzer.process({
        "2026-10-06 10:21:35",
        LogLevel::ERROR,
        "Database connection failed"
    });

    analyzer.process({
        "2026-10-06 10:22:35",
        LogLevel::ERROR,
        "Database connection failed"
    });

    analyzer.process({
        "2026-10-06 10:23:35",
        LogLevel::ERROR,
        "Timeout occurred"
    });

    auto errors = analyzer.getErrorMessages();

    EXPECT_EQ(errors["Database connection failed"], 2);
    EXPECT_EQ(errors["Timeout occurred"], 1);
}