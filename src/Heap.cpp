#include "Heap.h"
#include <algorithm>  // For std::swap

// Swap two rows in the data
void Heap::swapRows(std::vector<std::vector<std::string>>& data, size_t i, size_t j) {
    std::swap(data[i], data[j]);
}

// Heapify the data (to maintain the heap property)
void Heap::heapify(std::vector<std::vector<std::string>>& data, size_t n, size_t i, bool (*comp)(const std::string&, const std::string&)) {
    size_t largest = i; // Initialize largest as root
    size_t left = 2 * i + 1; // Left child
    size_t right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && comp(data[left][1], data[largest][1])) {
        largest = left;
    }

    // If right child is larger than root
    if (right < n && comp(data[right][1], data[largest][1])) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swapRows(data, i, largest);
        heapify(data, n, largest, comp); // Recursively heapify the affected subtree
    }
}

// Main heap sort function
void Heap::heapSort(std::vector<std::vector<std::string>>& data, size_t low, size_t high, bool (*comp)(const std::string&, const std::string&)) {
    size_t n = high + 1;

    // Build heap (rearrange the array)
    for (size_t i = n / 2 - 1; i < n; --i) {
        heapify(data, n, i, comp);
    }

    // One by one extract elements from heap
    for (size_t i = n - 1; i > low; --i) {
        swapRows(data, low, i);  // Move current root to end
        heapify(data, i, low, comp); // Call heapify on the reduced heap
    }
}
