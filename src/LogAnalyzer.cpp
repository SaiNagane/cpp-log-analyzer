#include "LogAnalyzer.h"

void LogAnalyzer::process(const LogEntry& entry) {
    std::lock_guard<std::mutex> lock(mutex_);

    ++totalCount_;

    switch (entry.level) {
        case LogLevel::INFO:
            ++infoCount_;
            break;

        case LogLevel::WARN:
            ++warnCount_;
            break;

        case LogLevel::ERROR:
            ++errorCount_;
            ++errorMessages_[entry.message];
            break;
    }
}

std::size_t LogAnalyzer::getTotalCount() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return totalCount_;
}

std::size_t LogAnalyzer::getInfoCount() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return infoCount_;
}

std::size_t LogAnalyzer::getWarnCount() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return warnCount_;
}

std::size_t LogAnalyzer::getErrorCount() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return errorCount_;
}

std::map<std::string, std::size_t> LogAnalyzer::getErrorMessages() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return errorMessages_;
}