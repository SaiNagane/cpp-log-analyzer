#include <gtest/gtest.h>

#include "LogParser.h"

TEST(LogParserTest, ParsesInfoLog) {
    LogParser parser;

    auto result = parser.parse(
        "2026-10-06 10:21:32 INFO User login successful"
    );

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->timestamp, "2026-10-06 10:21:32");
    EXPECT_EQ(result->level, LogLevel::INFO);
    EXPECT_EQ(result->message, "User login successful");
}

TEST(LogParserTest, ParsesWarnLog) {
    LogParser parser;

    auto result = parser.parse(
        "2026-10-06 10:21:37 WARN Retry attempt 2"
    );

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->level, LogLevel::WARN);
    EXPECT_EQ(result->message, "Retry attempt 2");
}

TEST(LogParserTest, ParsesErrorLog) {
    LogParser parser;

    auto result = parser.parse(
        "2026-10-06 10:21:35 ERROR Database connection failed"
    );

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->level, LogLevel::ERROR);
    EXPECT_EQ(result->message, "Database connection failed");
}

TEST(LogParserTest, RejectsEmptyLog) {
    LogParser parser;

    auto result = parser.parse("");

    EXPECT_FALSE(result.has_value());
}

TEST(LogParserTest, RejectsInvalidLog) {
    LogParser parser;

    auto result = parser.parse(
        "This is not a valid log"
    );

    EXPECT_FALSE(result.has_value());
}

TEST(LogParserTest, RejectsUnknownLogLevel) {
    LogParser parser;

    auto result = parser.parse(
        "2026-10-06 10:21:40 DEBUG Some debug message"
    );

    EXPECT_FALSE(result.has_value());
}

TEST(LogParserTest, RejectsLogWithoutMessage) {
    LogParser parser;

    auto result = parser.parse(
        "2026-10-06 10:21:40 ERROR"
    );

    EXPECT_FALSE(result.has_value());
}