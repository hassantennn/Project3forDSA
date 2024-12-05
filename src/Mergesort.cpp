#include "Mergesort.h"

void MergeSort::mergeSort(std::vector<std::vector<std::string>>& data, size_t low, size_t high, bool (*comp)(const std::string&, const std::string&)) {
    if (low < high) {
        size_t mid = (low + high) / 2;
        mergeSort(data, low, mid, comp);
        mergeSort(data, mid + 1, high, comp);
        merge(data, low, mid, high, comp);
    }
}

void MergeSort::merge(std::vector<std::vector<std::string>>& data, size_t low, size_t mid, size_t high, bool (*comp)(const std::string&, const std::string&)) {
    size_t n1 = mid - low + 1;
    size_t n2 = high - mid;

    std::vector<std::vector<std::string>> left(data.begin() + low, data.begin() + mid + 1);
    std::vector<std::vector<std::string>> right(data.begin() + mid + 1, data.begin() + high + 1);

    size_t i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (comp(left[i][1], right[j][1])) { // Compare by Date (column 1)
            data[k++] = left[i++];
        } else {
            data[k++] = right[j++];
        }
    }

    while (i < n1) {
        data[k++] = left[i++];
    }
    while (j < n2) {
        data[k++] = right[j++];
    }
}
