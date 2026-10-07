#include <gtest/gtest.h>

#include "LogProcessor.h"

TEST(LogProcessorTest, ProcessesLogsUsingMultipleWorkers) {
    LogProcessor processor(4);

    constexpr int totalLogs = 1000;

    for (int i = 0; i < totalLogs; ++i) {
        LogLevel level;

        if (i % 3 == 0) {
            level = LogLevel::INFO;
        } else if (i % 3 == 1) {
            level = LogLevel::WARN;
        } else {
            level = LogLevel::ERROR;
        }

        processor.submit({
            "2026-10-06 10:21:32",
            level,
            "Test log message"
        });
    }

    processor.finish();

    const LogAnalyzer& analyzer = processor.getAnalyzer();

    EXPECT_EQ(analyzer.getTotalCount(), 1000);
    EXPECT_EQ(analyzer.getInfoCount(), 334);
    EXPECT_EQ(analyzer.getWarnCount(), 333);
    EXPECT_EQ(analyzer.getErrorCount(), 333);
}