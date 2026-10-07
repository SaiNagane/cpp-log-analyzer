# Multithreaded Log Analyzer

A multithreaded log analysis system built with modern C++17. The application parses application logs, processes entries concurrently using worker threads, and generates statistics for INFO, WARN, and ERROR events.

## Features

* Parses structured application log files
* Supports INFO, WARN, and ERROR log levels
* Multithreaded log processing using `std::thread`
* Thread-safe producer-consumer queue
* Concurrent statistics aggregation
* Identifies repeated error messages
* Handles invalid log entries safely
* Unit testing with GoogleTest
* CMake-based build system
* Automated build and test using GitHub Actions

## Architecture

```text
Application Log
      |
      v
+-------------+
|  LogParser  |
+-------------+
      |
      v
+----------------------+
| ThreadSafeQueue      |
| Producer-Consumer    |
+----------------------+
      |
      v
+----------------------+
| Worker Threads       |
| std::thread          |
+----------------------+
      |
      v
+----------------------+
|    LogAnalyzer       |
| Statistics & Errors  |
+----------------------+
      |
      v
Summary Report
```

## Tech Stack

* C++17
* STL
* CMake
* GoogleTest
* Git & GitHub
* GitHub Actions
* Multithreading
* Mutex & Condition Variable

## Project Structure

```text
cpp-log-analyzer/
├── .github/
│   └── workflows/
│       └── ci.yml
├── include/
│   ├── LogEntry.h
│   ├── LogParser.h
│   ├── ThreadSafeQueue.h
│   ├── LogAnalyzer.h
│   └── LogProcessor.h
├── src/
│   ├── main.cpp
│   ├── LogParser.cpp
│   ├── LogAnalyzer.cpp
│   └── LogProcessor.cpp
├── tests/
│   ├── LogParserTest.cpp
│   ├── LogAnalyzerTest.cpp
│   ├── LogProcessorTest.cpp
│   └── ThreadSafeQueueTest.cpp
├── data/
│   └── sample.log
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Build

Clone the repository:

```bash
git clone https://github.com/SaiNagane/cpp-log-analyzer.git
cd cpp-log-analyzer
```

Configure the project:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

## Run

Run the analyzer with the sample log file:

```bash
./build/log_analyzer data/sample.log
```

On Windows with MinGW:

```bash
build/log_analyzer.exe data/sample.log
```

## Example Output

```text
===== Log Analysis Summary =====

Total entries : 10
INFO          : 4
WARN          : 3
ERROR         : 3

===== Error Messages =====
2x - Database connection failed
1x - Timeout occurred
```

## Testing

The project uses GoogleTest for automated unit testing.

Run:

```bash
ctest --test-dir build --output-on-failure
```

The test suite covers:

* Log parsing
* Valid and invalid log entries
* Log level classification
* Error aggregation
* Thread-safe queue operations
* Multithreaded log processing

Current test suite: **10 tests passing**

## Continuous Integration

GitHub Actions automatically:

1. Checks out the repository
2. Installs CMake and g++
3. Configures the project
4. Builds the application
5. Runs the complete test suite

Every push and pull request to the `main` or `master` branch is automatically validated.

## Key C++ Concepts Demonstrated

This project demonstrates practical use of:

* Object-Oriented Programming
* STL containers
* `std::thread`
* `std::mutex`
* `std::lock_guard`
* `std::unique_lock`
* `std::condition_variable`
* `std::optional`
* RAII
* Producer-consumer pattern
* Exception handling
* Unit testing
* CMake

## Future Improvements

* Support larger log files with configurable worker counts
* Add filtering by timestamp and log level
* Export analysis results to JSON or CSV
* Add configurable log formats
* Add performance benchmarking

## Author

**Sai Nagane**

Software Engineer | Java & C++

[GitHub](https://github.com/SaiNagane)

[LinkedIn](https://www.linkedin.com/in/sainagane/)
