cmake_minimum_required(VERSION 3.16)
project(StockMarketAnalysisSystem)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB SRC_SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Gather test files
file(GLOB TEST_SOURCES
        ${PROJECT_SOURCE_DIR}/tests/*.cpp
)

# Create the executable target
add_executable(StockMarketAnalysisSystem
        ${SRC_SOURCES}
        ${TEST_SOURCES}
)


# Specify include directories for the target
target_include_directories(StockMarketAnalysisSystem PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/lib/json
)

# Debugging information
message(STATUS "Source Files: ${SRC_SOURCES}")
message(STATUS "Test Files: ${TEST_SOURCES}")
message(STATUS "Include Directories: ${PROJECT_SOURCE_DIR}/include, ${PROJECT_SOURCE_DIR}/lib/json")

# Optional: Add any required libraries here
# Example: target_link_libraries(StockMarketAnalysisSystem <library_name>)
