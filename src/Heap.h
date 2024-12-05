#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

// Heap sort class
class Heap {
public:
    void heapSort(std::vector<std::vector<std::string>>& data, size_t low, size_t high, bool (*comp)(const std::string&, const std::string&));
private:
    void heapify(std::vector<std::vector<std::string>>& data, size_t n, size_t i, bool (*comp)(const std::string&, const std::string&));
    void swapRows(std::vector<std::vector<std::string>>& data, size_t i, size_t j);
};

#endif // HEAP_H
