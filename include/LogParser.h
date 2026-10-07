#pragma once

#include "LogEntry.h"

#include <optional>
#include <string>

class LogParser {
public:
    std::optional<LogEntry> parse(const std::string& line) const;

private:
    LogLevel parseLogLevel(const std::string& level) const;
};