#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h> // For getcwd
#include "PerformanceCalculator.h"
#include "StockDataProcessor.h"
#include "json.hpp" // JSON library
#include "httplib.h" // HTTP server library

bool compareDates(const std::string& date1, const std::string& date2) {
    std::tm tm1 = {};
    std::tm tm2 = {};
    std::stringstream ss1(date1);
    std::stringstream ss2(date2);

    ss1 >> std::get_time(&tm1, "%Y-%m-%d");
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");

    if (ss1.fail() || ss2.fail()) {
        return false; // Invalid date format
    }

    return std::mktime(&tm1) < std::mktime(&tm2);
}

std::string getProjectRoot() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::string currentDir(cwd);
        size_t pos = currentDir.find("/cmake-build-debug");
        if (pos != std::string::npos) {
            return currentDir.substr(0, pos); // Strip the build directory
        }
    }
    return "";
}

// Add CORS headers to the response
void setCORSHeaders(httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

using json = nlohmann::json;

int main() {
    std::string projectRoot = getProjectRoot();
    if (projectRoot.empty()) {
        std::cerr << "Error: Unable to determine project root." << std::endl;
        return 1;
    }

    httplib::Server svr;

    // Handle preflight requests for CORS
    svr.Options("/.*", [&](const httplib::Request&, httplib::Response& res) {
        setCORSHeaders(res);
        res.status = 204; // No Content
    });

    svr.Post("/compare", [&](const httplib::Request& req, httplib::Response& res) {
        setCORSHeaders(res); // Add CORS headers

        // Parse JSON input
        json input;
        try {
            input = json::parse(req.body);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content("Invalid JSON input: " + std::string(e.what()), "text/plain");
            return;
        }

        // Resolve file paths
        std::string file1 = projectRoot + "/" + input["file1"].get<std::string>();
        std::string file2 = projectRoot + "/" + input["file2"].get<std::string>();

        StockDataProcessor processor;
        PerformanceCalculator performanceCalculator;
        json results;

        for (const std::string& file : {file1, file2}) {
            std::cout << "Processing file: " << file << std::endl;

            auto data = processor.readCSV(file);
            if (data.empty()) {
                std::cerr << "Error: Unable to open or process file: " << file << std::endl;
                res.status = 500;
                res.set_content("Error processing file: " + file, "text/plain");
                return;
            }

            auto aggregatedData = performanceCalculator.aggregateByDate(data);
            performanceCalculator.calculateMergeSortTime(aggregatedData, compareDates);
            performanceCalculator.calculateHeapSortTime(aggregatedData, compareDates);

            double sharpeRatio = performanceCalculator.calculateSharpeRatio(aggregatedData, 1.5); // Example risk-free rate
            double totalReturn = performanceCalculator.calculateTotalReturn(aggregatedData);

            results[file] = {
                {"merge_sort_time_ms", performanceCalculator.getMergeSortTime()},
                {"heap_sort_time_ms", performanceCalculator.getHeapSortTime()},
                {"sharpe_ratio", sharpeRatio},
                {"total_return", totalReturn}
            };
        }

        // Log results
        std::cout << "Comparison results:\n" << results.dump(4) << std::endl;

        // Send JSON response
        res.set_content(results.dump(4), "application/json");
    });

    svr.Get("/health", [&](const httplib::Request&, httplib::Response& res) {
        setCORSHeaders(res);
        res.set_content("{\"status\":\"OK\"}", "application/json");
    });

    std::cout << "Server is running on http://localhost:8000" << std::endl;
    svr.listen("localhost", 8000);

    return 0;
}
