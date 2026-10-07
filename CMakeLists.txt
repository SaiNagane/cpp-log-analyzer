cmake_minimum_required(VERSION 3.20)

project(CppLogAnalyzer
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# -----------------------------
# Main Application
# -----------------------------

add_executable(
    log_analyzer
    src/main.cpp
    src/LogParser.cpp
    src/LogAnalyzer.cpp
    src/LogProcessor.cpp
)

target_include_directories(
    log_analyzer
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# -----------------------------
# Tests
# -----------------------------

enable_testing()

add_executable(
    log_analyzer_tests
    tests/LogParserTest.cpp
    tests/ThreadSafeQueueTest.cpp
    tests/LogAnalyzerTest.cpp
    tests/LogProcessorTest.cpp
    src/LogParser.cpp
    src/LogAnalyzer.cpp
    src/LogProcessor.cpp
)

target_include_directories(
    log_analyzer_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    log_analyzer_tests
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(log_analyzer_tests)