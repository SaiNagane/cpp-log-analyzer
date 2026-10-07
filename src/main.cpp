#include "LogParser.h"
#include "LogProcessor.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: log_analyzer <log_file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open log file: "
                  << argv[1] << '\n';
        return 1;
    }

    LogParser parser;

    // Use multiple worker threads for concurrent log processing.
    LogProcessor processor(4);

    std::string line;

    while (std::getline(inputFile, line)) {
        auto entry = parser.parse(line);

        if (entry.has_value()) {
            processor.submit(std::move(entry.value()));
        }
    }

    processor.finish();

    const LogAnalyzer& analyzer = processor.getAnalyzer();

    std::cout << "\n===== Log Analysis Summary =====\n\n";

    std::cout << "Total entries : "
              << analyzer.getTotalCount() << '\n';

    std::cout << "INFO          : "
              << analyzer.getInfoCount() << '\n';

    std::cout << "WARN          : "
              << analyzer.getWarnCount() << '\n';

    std::cout << "ERROR         : "
              << analyzer.getErrorCount() << '\n';

    std::cout << "\n===== Error Messages =====\n";

    auto errors = analyzer.getErrorMessages();

    if (errors.empty()) {
        std::cout << "No errors found.\n";
    } else {
        for (const auto& [message, count] : errors) {
            std::cout << count << "x - " << message << '\n';
        }
    }

    return 0;
}