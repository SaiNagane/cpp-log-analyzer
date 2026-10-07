#pragma once

#include "LogAnalyzer.h"
#include "ThreadSafeQueue.h"

#include <cstddef>
#include <thread>
#include <vector>

class LogProcessor {
public:
    explicit LogProcessor(std::size_t workerCount);

    void submit(LogEntry entry);

    void finish();

    const LogAnalyzer& getAnalyzer() const;

private:
    void worker();

    ThreadSafeQueue<LogEntry> queue_;
    LogAnalyzer analyzer_;
    std::vector<std::thread> workers_;
};