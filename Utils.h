#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

void emptyFile(const std::string& filename);

bool fileToVector(const std::string& filename, std::vector<int>& values);

void writeHeaderIfEmpty(const std::string& filename, const std::string& header);

void appendCSVRow(const std::string& filename, const std::string& row);


void merge(std::vector<std::pair<double, int>>& arr, int left, int mid, int right, int& opCount);
void mergeSort(std::vector<std::pair<double, int>>& arr, int left, int right, int& opCount);

#endif