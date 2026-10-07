#include "LogProcessor.h"

#include <utility>

LogProcessor::LogProcessor(std::size_t workerCount) {
    for (std::size_t i = 0; i < workerCount; ++i) {
        workers_.emplace_back(&LogProcessor::worker, this);
    }
}

void LogProcessor::submit(LogEntry entry) {
    queue_.push(std::move(entry));
}

void LogProcessor::finish() {
    queue_.finish();

    for (auto& workerThread : workers_) {
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }
}

const LogAnalyzer& LogProcessor::getAnalyzer() const {
    return analyzer_;
}

void LogProcessor::worker() {
    LogEntry entry;

    while (queue_.pop(entry)) {
        analyzer_.process(entry);
    }
}