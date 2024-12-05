#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <string>

class MergeSort {
public:
    // Main function to sort data using MergeSort
    void mergeSort(std::vector<std::vector<std::string>>& data, size_t low, size_t high, bool (*comp)(const std::string&, const std::string&));

private:
    // Helper function to merge two sorted halves of the data
    void merge(std::vector<std::vector<std::string>>& data, size_t low, size_t mid, size_t high, bool (*comp)(const std::string&, const std::string&));
};

#endif // MERGESORT_H
