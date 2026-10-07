#pragma once

#include "LogEntry.h"

#include <cstddef>
#include <map>
#include <mutex>
#include <string>

class LogAnalyzer {
public:
    void process(const LogEntry& entry);

    std::size_t getTotalCount() const;
    std::size_t getInfoCount() const;
    std::size_t getWarnCount() const;
    std::size_t getErrorCount() const;

    std::map<std::string, std::size_t> getErrorMessages() const;

private:
    mutable std::mutex mutex_;

    std::size_t totalCount_ = 0;
    std::size_t infoCount_ = 0;
    std::size_t warnCount_ = 0;
    std::size_t errorCount_ = 0;

    std::map<std::string, std::size_t> errorMessages_;
};