#ifndef PERFORMANCECALCULATOR_H
#define PERFORMANCECALCULATOR_H

#include <vector>
#include <string>

class PerformanceCalculator {
public:

    std::vector<double> calculateDailyReturns(const std::vector<std::vector<std::string>>& aggregatedData);

    double calculateSharpeRatio(const std::vector<std::vector<std::string>>& aggregatedData, double riskFreeRate);

    std::vector<std::vector<std::string>> aggregateByDate(const std::vector<std::vector<std::string>>& data);

    static double calculateTotalReturn(const std::vector<std::vector<std::string>>& data);

    // Method to calculate and store Merge Sort time
    void calculateMergeSortTime(std::vector<std::vector<std::string>>& data, bool (*comp)(const std::string&, const std::string&));

    // Method to calculate and store Heap Sort time
    void calculateHeapSortTime(std::vector<std::vector<std::string>>& data, bool (*comp)(const std::string&, const std::string&));

    // Get the recorded time for Merge Sort
    long long getMergeSortTime() const;

    // Get the recorded time for Heap Sort
    long long getHeapSortTime() const;

private:
    long long mergeSortTime = 0;  // Time for Merge Sort in milliseconds
    long long heapSortTime = 0;   // Time for Heap Sort in milliseconds
};

#endif
