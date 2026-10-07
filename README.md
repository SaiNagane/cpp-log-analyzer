[![C++ Build and Test](https://github.com/SaiNagane/cpp-log-analyzer/actions/workflows/ci.yml/badge.svg)](https://github.com/SaiNagane/cpp-log-analyzer/actions/workflows/ci.yml)

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

The application follows a producer-consumer architecture:

```text
                         Application Log File
                                  |
                                  v
                         +------------------+
                         |    LogParser     |
                         | Parse & Validate |
                         +--------+---------+
                                  |
                                  | LogEntry
                                  v
                    +---------------------------+
                    |    ThreadSafeQueue<T>     |
                    | Mutex + Condition Variable|
                    +-------------+-------------+
                                  |
                    +-------------+-------------+
                    |             |             |
                    v             v             v
               +---------+   +---------+   +---------+
               | Worker  |   | Worker  |   | Worker  |
               | Thread  |   | Thread  |   | Thread  |
               +----+----+   +----+----+   +----+----+
                    |             |             |
                    +-------------+-------------+
                                  |
                                  v
                         +------------------+
                         |   LogAnalyzer    |
                         | Thread-Safe      |
                         | Statistics       |
                         +--------+---------+
                                  |
                                  v
                         +------------------+
                         | Analysis Summary |
                         | INFO / WARN /    |
                         | ERROR / Errors   |
                         +------------------+
```

### Component Responsibilities

| Component            | Responsibility                                                              |
| -------------------- | --------------------------------------------------------------------------- |
| **LogParser**        | Parses raw log lines and converts them into structured `LogEntry` objects   |
| **ThreadSafeQueue**  | Safely transfers parsed log entries between the producer and worker threads |
| **Worker Threads**   | Consume log entries concurrently and pass them to the analyzer              |
| **LogAnalyzer**      | Maintains thread-safe statistics and aggregates repeated error messages     |
| **Main Application** | Reads the input file, coordinates processing, and displays the final report |

### Processing Flow

1. `main.cpp` reads the application log file line by line.
2. `LogParser` validates and converts each line into a `LogEntry`.
3. Valid entries are submitted to the thread-safe queue.
4. Multiple worker threads consume entries concurrently.
5. `LogAnalyzer` updates INFO, WARN, ERROR, and error-frequency statistics.
6. Worker threads are joined after all entries are processed.
7. The application prints the final analysis summary.

The PlantUML source for the architecture is available in [`diagram.puml`](./diagram.puml).


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
