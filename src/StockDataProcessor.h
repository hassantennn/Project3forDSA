#ifndef STOCKDATAPROCESSOR_H
#define STOCKDATAPROCESSOR_H

#include <string>
#include <vector>
#include <map>

class StockDataProcessor {
public:

    // Reads a CSV file and returns a 2D vector
    std::vector<std::vector<std::string>> readCSV(const std::string& filename);

    // Preprocesses data by removing rows with missing or empty values
    void preprocessData(std::vector<std::vector<std::string>>& data);

    // Update the function declaration to accept the 'excludeNegatives' parameter
    double calculateAverageClose(const std::vector<std::vector<std::string>>& data);;

    // Prints the 2D vector data for debugging purposes
    void printData(const std::vector<std::vector<std::string>>& data);
};

#endif // STOCKDATAPROCESSOR_H
