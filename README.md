# Stock Market Analysis System

## Instructions:
This code uses functions that only run on IOS not Windows. 
1. Run code
2. Open SRC directory
3. Open html file
4. Click Google Chrome Icon to open pop up interface
5. Select two companies on left side selection
6. Click compare to display results

## Project Overview

The **Stock Market Analysis System** is a project by the **HHD Squad** (Muhammad Hassan, Haya Shaikh, Diego Curbelo). The primary goal is to analyze stock performance and determine which companies or sectors perform best based on financial metrics like **Total Return**, **CAGR**, and **Sharpe Ratio**. This system also compares the efficiency of processing large stock datasets using **Heaps** and **Red Black Trees**.

## Table of Contents

- [Project Overview](#project-overview)
- [Problem Statement](#problem-statement)
- [Motivation](#motivation)
- [Features](#features)
- [Data Sources](#data-sources)
- [Tools and Technologies](#tools-and-technologies)
- [Project Structure](#project-structure)

## Problem Statement

This project aims to address two main challenges:
1. **Efficiency**: Compare the efficiency of different data structures (Heaps vs. Red Black Trees) in processing large stock datasets.
2. **Financial Insight**: Identify profitable investments by analyzing financial metrics to determine the best-performing companies or sectors.

## Motivation

Stock market investments can be complex, and many people lack the knowledge or time to analyze data. This project simplifies stock analysis and recommends profitable investments based on historical performance and user inputs.

## Features

- **Efficient Stock Data Processing**: Utilize Heaps and Red Black Trees to handle large datasets.
- **Financial Analysis Metrics**:
  - **Total Return**
  - **Compound Annual Growth Rate (CAGR)**
  - **Sharpe Ratio**
- **User Interface**: Provide a user-friendly interface for displaying investment recommendations.
- **Real-time Data Integration**: Fetch stock data from various public APIs for up-to-date analysis.

## Data Sources

We use public datasets and APIs to retrieve stock data. These include:
- [Alpha Vantage](https://www.alphavantage.co/documentation/)
- [Yahoo Finance API on RapidAPI](https://rapidapi.com/sparior/api/yahoo-finance15)
- [Nasdaq Data Link](https://docs.data.nasdaq.com/)
- [IEX Cloud](https://iexcloud.io/docs/core/fundamentals)

## Tools and Technologies

- **Programming Languages**: C++ for backend processing, Python (Flask or wxWidgets) for the user interface.
- **Data Structures**: Heaps and Red Black Trees for efficient stock data handling.
- **APIs**: Public stock data APIs to retrieve and process financial data.
- **Libraries**:
  - `nlohmann/json` for JSON parsing (if required for API responses).
  - Other C++ libraries as necessary for API integration and data handling.

## Project Structure

```plaintext
StockMarketAnalysisSystem/
├── src/                    # C++ source files
│   ├── main.cpp            # Main application entry point
│   ├── StockDataProcessor.cpp  # Handles API integration and data processing
│   ├── Heap.cpp            # Heap data structure implementation
│   ├── RedBlackTree.cpp    # Red Black Tree data structure implementation
│   └── PerformanceCalculator.cpp  # Calculates financial metrics
├── include/                # Header files
│   ├── StockDataProcessor.h
│   ├── Heap.h
│   ├── RedBlackTree.h
│   └── PerformanceCalculator.h
├── data/                   # Data files (e.g., sample stock data)
├── tests/                  # Unit tests
├── lib/                    # Third-party libraries (e.g., JSON library)
│   └── json/               # JSON parsing library files
└── CMakeLists.txt          # CMake build configuration
