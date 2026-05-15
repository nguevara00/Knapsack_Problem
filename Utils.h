#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

bool fileToVector(const std::string& filename, std::vector<int>& values);
void merge(std::vector<std::pair<double, int>>& arr, int left, int mid, int right, int& opCount);
void mergeSort(std::vector<std::pair<double, int>>& arr, int left, int right, int& opCount);

#endif