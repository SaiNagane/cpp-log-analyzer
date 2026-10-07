#pragma once

#include <string>

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

struct LogEntry {
    std::string timestamp;
    LogLevel level;
    std::string message;
};