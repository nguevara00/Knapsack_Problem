#include <iostream>
#include <fstream>
#include <utility>
#include "Utils.h"

//includes file handling and merge sort

bool fileToVector(const std::string& filename, std::vector<int>& values) {
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    int value;

    while (inputFile >> value) {
        values.push_back(value);
    }

    return true;
}

void emptyFile(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::trunc);
    outFile.close();
}

void writeHeaderIfEmpty(const std::string& filename, const std::string& header) {
    std::ifstream checkFile(filename);

    bool isEmpty = !checkFile.good() || checkFile.peek() == std::ifstream::traits_type::eof();
    checkFile.close();

    if (isEmpty) {
        std::ofstream outFile(filename, std::ios::app);
        outFile << header << '\n';
    }
}

void appendCSVRow(const std::string& filename, const std::string& row) {
    std::ofstream outFile(filename, std::ios::app);
    outFile << row << '\n';
}

void merge(std::vector<std::pair<double, int>>& arr, int left, int mid, int right, int& opCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    // create temp arrays
    std::vector<std::pair<double, int>> L(n1);
    std::vector<std::pair<double, int>> R(n2);

    // copy & merge data to temp arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        opCount++;
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        opCount++;
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        opCount++;

        if (L[i] >= R[j]) {   // sort in descending order based on ratio
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        opCount++;
        arr[k] = L[i];
        i++;
        k++;
    } // copy the remaining elements of R, if there are any

    while (j < n2) {
        opCount++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::pair<double, int>>& arr, int left, int right, int& opCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, opCount); // sort first half
        mergeSort(arr, mid + 1, right, opCount); // sort second half
        merge(arr, left, mid, right, opCount); // merge the sorted halves
    }
}