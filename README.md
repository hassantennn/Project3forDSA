# Stock Market Analysis System

## Project Overview

The **Stock Market Analysis System** is a project by the **HHD Squad** (Muhammad Hassan, Haya Shaikh, Diego Curbelo). The primary goal is to analyze stock performance and determine which companies or sectors perform best based on financial metrics like **Total Return** and **Sharpe Ratio**. This system also compares the efficiency of processing large stock datasets using **Heaps** and **Merge Sort**.

## Table of Contents

- [Project Overview](#project-overview)
- [Problem Statement](#problem-statement)
- [Motivation](#motivation)
- [Features](#features)
- [Tools and Technologies](#tools-and-technologies)
- [Project Structure](#project-structure)
- Instructions(#how-to-use-our-code)

## Problem Statement

This project aims to address two main challenges:
1. **Efficiency**: Compare the efficiency of different data structures (Heaps vs. Merge Sort) in processing large stock datasets.
2. **Financial Insight**: Identify profitable investments by analyzing financial metrics to determine the best-performing companies or sectors.

## Motivation

Stock market investments can be complex, and many people lack the knowledge or time to analyze data. This project simplifies stock analysis and recommends profitable investments based on historical performance and user inputs.

## Features

- **Efficient Stock Data Processing**: Utilize Heaps and Merge Sort to handle large datasets.
- **Financial Analysis Metrics**:
  - **Total Return**
  - **Sharpe Ratio**
- **User Interface**: Provide a user-friendly interface for displaying investment recommendations.
- **Real-time Data Integration**: Fetch stock data from various public APIs for up-to-date analysis.

## Tools and Technologies

- **Programming Languages**: C++ for backend processing, Javascript for the user interface.
- **Data Structures**: Heaps and Merge Sort Algorithms for efficient stock data handling.
- **Libraries**:
  - `nlohmann/json` for JSON parsing (if required for data responses).
  - Other C++ libraries as necessary for data integration and data handling.

## Project Structure

```plaintext
StockMarketAnalysisSystem/
├── src/                    # C++ source files
│   ├── html
    │   ├── dashboard.html
│   ├── StockDataProcessor.cpp  # Handles API integration and data processing
│   ├── Heap.cpp            # Heap data structure implementation
│   ├── MergeSort.cpp    # Red Black Tree data structure implementation
│   └── PerformanceCalculator.cpp  # Calculates financial metrics
│   └── json/               
│   └── httplib.h
├── include/                # Header files
│   ├── StockDataProcessor.h
│   ├── Heap.h
│   ├── MergeSort.h
│   └── PerformanceCalculator.h
├── data/                   # Data files (e.g., sample stock data)
├── tests/                  # Unit tests
                            # Third-party libraries (e.g., JSON library)

└── CMakeLists.txt          # CMake build configuration

## How To Use Our Code
1) Download all files from our GitHub (including the 30 csv company files)
2) Move all csv files inside the "dataa" file
2) Run code through terminal
3) Go to src/html/dashboard.html and a bar pops up on the right-hand side of the screen with little icons: FireFox, Google Chrome, etc.
4) Click Google Chrome icon which directs you to the website
5) On the left-hand side of the website, there is the list of 30 companies - choose TWO of them and click the Compare button
6) The program outputs the Heap Sort Time, Merge Sort Time, Sharpe Ratio, and Total Return, as well as the recommendation of which company our program recommends. Additionally, there is a graph which shows a visual for the heap sort time versus the merge sort time of the two companies selected.
