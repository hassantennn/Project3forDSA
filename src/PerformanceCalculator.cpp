#include "PerformanceCalculator.h"
#include <chrono>  // For time calculation
#include "Mergesort.h"
#include "Heap.h"
#include <iostream>
#include <numeric>
#include <map>



std::vector<double> PerformanceCalculator::calculateDailyReturns(const std::vector<std::vector<std::string>>& aggregatedData) {
    std::vector<double> dailyReturns;

    for (size_t i = 2; i < aggregatedData.size(); ++i) { // Start from 2 to skip the header row
        try {
            double closeToday = std::stod(aggregatedData[i][5]);
            double closeYesterday = std::stod(aggregatedData[i - 1][5]);
            double dailyReturn = ((closeToday - closeYesterday) / closeYesterday) * 100.0;
            dailyReturns.push_back(dailyReturn);
        } catch (...) {
            continue; // Skip invalid rows
        }
    }

    return dailyReturns;
}


double PerformanceCalculator::calculateSharpeRatio(const std::vector<std::vector<std::string>>& aggregatedData, double riskFreeRate) {
    if (aggregatedData.size() < 3) { // At least two data points plus header
        std::cerr << "Error: Not enough data points to calculate Sharpe Ratio." << std::endl;
        return 0.0;
    }

    std::vector<double> dailyReturns;

    // Calculate daily returns from aggregated Close prices
    for (size_t i = 2; i < aggregatedData.size(); ++i) { // Start from 2 to skip the header row
        try {
            double closeToday = std::stod(aggregatedData[i][5]);       // Current day's Close
            double closeYesterday = std::stod(aggregatedData[i - 1][5]); // Previous day's Close
            double dailyReturn = ((closeToday - closeYesterday) / closeYesterday) * 100.0; // Percentage change
            dailyReturns.push_back(dailyReturn);
        } catch (...) {
            continue; // Skip rows with invalid data
        }
    }

    if (dailyReturns.empty()) {
        std::cerr << "Error: No valid daily returns calculated." << std::endl;
        return 0.0;
    }

    // Calculate average daily return
    double totalReturn = std::accumulate(dailyReturns.begin(), dailyReturns.end(), 0.0);
    double avgReturn = totalReturn / dailyReturns.size();

    // Calculate standard deviation of daily returns
    double variance = 0.0;
    for (double dailyReturn : dailyReturns) {
        variance += std::pow(dailyReturn - avgReturn, 2);
    }
    variance /= dailyReturns.size();
    double stdDev = std::sqrt(variance);

    // Calculate Sharpe Ratio
    double sharpeRatio = (avgReturn - riskFreeRate) / stdDev;

    return sharpeRatio;
}

std::vector<std::vector<std::string>> PerformanceCalculator::aggregateByDate(const std::vector<std::vector<std::string>>& data) {
    std::map<std::string, std::vector<double>> dateToCloseValues;

    // Group Close values by Date
    for (size_t i = 1; i < data.size(); ++i) { // Start from 1 to skip the header
        try {
            std::string date = data[i][1]; // Date column
            double close = std::stod(data[i][5]); // Close column
            dateToCloseValues[date].push_back(close);
        } catch (...) {
            continue; // Skip invalid rows
        }
    }

    // Create a new dataset with aggregated values
    std::vector<std::vector<std::string>> aggregatedData;
    aggregatedData.push_back(data[0]); // Copy the header row

    for (const auto& [date, closes] : dateToCloseValues) {
        double aggregatedClose = std::accumulate(closes.begin(), closes.end(), 0.0) / closes.size(); // Average
        aggregatedData.push_back({data[0][0], date, "0", "0", "0", std::to_string(aggregatedClose), "0"}); // Fill other columns with placeholders
    }

    return aggregatedData;
}


double PerformanceCalculator::calculateTotalReturn(const std::vector<std::vector<std::string>>& data) {
    if (data.size() < 2) {
        return 0.0; // Insufficient data, return 0.0
    }

    // Initialize variables
    double startPrice = -1.0;
    double endPrice = -1.0;

    // Find the first positive "Close" value from the beginning
    for (size_t i = 1; i < data.size(); ++i) { // Start from row 1 to skip the header
        try {
            startPrice = std::stod(data[i][5]); // Accessing the "Close" column at index 5
            if (startPrice > 0.0) {
                break; // Exit once a positive value is found
            }
        } catch (...) {
            continue; // Skip rows with invalid "Close" values
        }
    }

    // Find the last positive "Close" value from the end
    for (size_t i = data.size() - 1; i > 0; --i) { // Start from the last row
        try {
            endPrice = std::stod(data[i][5]); // Accessing the "Close" column at index 5
            if (endPrice > 0.0) {
                break; // Exit once a positive value is found
            }
        } catch (...) {
            continue; // Skip rows with invalid "Close" values
        }
    }

    // Ensure both prices are valid
    if (startPrice <= 0.0 || endPrice <= 0.0) {
        return 0.0; // Return 0 if valid prices cannot be found
    }

    // Calculate the total return
    double totalReturn = ((endPrice - startPrice) / startPrice) * 100;

    return totalReturn;
}




// Method to calculate and store Merge Sort time
void PerformanceCalculator::calculateMergeSortTime(std::vector<std::vector<std::string>>& data, bool (*comp)(const std::string&, const std::string&)) {
    MergeSort mergesort;

    auto start = std::chrono::high_resolution_clock::now();
    mergesort.mergeSort(data, 1, data.size() - 1, comp);  // Sorting by the second column (Date)
    auto end = std::chrono::high_resolution_clock::now();

    mergeSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();  // Store time in milliseconds
}

// Method to calculate and store Heap Sort time
void PerformanceCalculator::calculateHeapSortTime(std::vector<std::vector<std::string>>& data, bool (*comp)(const std::string&, const std::string&)) {
    Heap heapSort;

    auto start = std::chrono::high_resolution_clock::now();
    heapSort.heapSort(data, 0, data.size() - 1, comp);  // Sorting by the second column (Date), use full range (0 to data.size()-1)
    auto end = std::chrono::high_resolution_clock::now();

    heapSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();  // Store time in milliseconds
}

// Get the recorded time for Merge Sort
long long PerformanceCalculator::getMergeSortTime() const {
    return mergeSortTime;
}

// Get the recorded time for Heap Sort
long long PerformanceCalculator::getHeapSortTime() const {
    return heapSortTime;
}
