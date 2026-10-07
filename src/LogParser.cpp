#include "LogParser.h"

#include <sstream>
#include <stdexcept>

std::optional<LogEntry> LogParser::parse(const std::string& line) const {
    if (line.empty()) {
        return std::nullopt;
    }

    std::istringstream stream(line);

    std::string date;
    std::string time;
    std::string level;
    std::string message;

    if (!(stream >> date >> time >> level)) {
        return std::nullopt;
    }

    std::getline(stream, message);

    // Remove the leading space from the message.
    if (!message.empty() && message.front() == ' ') {
        message.erase(0, 1);
    }

    if (message.empty()) {
        return std::nullopt;
    }

    try {
        LogLevel logLevel = parseLogLevel(level);

        return LogEntry{
            date + " " + time,
            logLevel,
            message
        };
    }
    catch (const std::invalid_argument&) {
        return std::nullopt;
    }
}

LogLevel LogParser::parseLogLevel(const std::string& level) const {
    if (level == "INFO") {
        return LogLevel::INFO;
    }

    if (level == "WARN") {
        return LogLevel::WARN;
    }

    if (level == "ERROR") {
        return LogLevel::ERROR;
    }

    throw std::invalid_argument("Unknown log level");
}