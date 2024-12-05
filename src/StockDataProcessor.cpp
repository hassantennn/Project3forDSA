#include "StockDataProcessor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

// Reads a CSV file and returns a 2D vector
std::vector<std::vector<std::string>> StockDataProcessor::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return data; // Return empty vector if file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell); // Add each cell to the row
        }

        data.push_back(row); // Add the row to the data
    }

    file.close();
    return data;
}

// Preprocesses data by removing rows with missing or empty values
void StockDataProcessor::preprocessData(std::vector<std::vector<std::string>>& data) {
    data.erase(
        std::remove_if(data.begin(), data.end(),
            [](const std::vector<std::string>& row) {
                // Check if any cell in the row is empty
                return std::any_of(row.begin(), row.end(),
                    [](const std::string& cell) { return cell.empty(); });
            }) ,
        data.end()
    );
}

double StockDataProcessor::calculateAverageClose(const std::vector<std::vector<std::string>>& data) {
    size_t closeColumnIndex = 4; // "Close" column index (5th column, index 4)
    double sum = 0.0;
    size_t count = 0;

    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() > closeColumnIndex && !data[i][closeColumnIndex].empty()) {
            try {
                double closeValue = std::stod(data[i][closeColumnIndex]);
                if (closeValue >= 0) {
                    sum += closeValue;
                    ++count;
                }
            } catch (const std::invalid_argument&) {
                continue;
            }
        }
    }

    return (count > 0) ? (sum / count) : 0.0;
}

// Prints the 2D vector data for debugging purposes
void StockDataProcessor::printData(const std::vector<std::vector<std::string>>& data) {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}
