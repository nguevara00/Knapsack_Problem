// Nick Guevara William Dappen
// CS 415 Gill
// Project 4 - Knapsack
// 5-9-2026

/*
Task Tracking -

	PROGRAMMING -
		all tasks working
        refactor 1a, 1b, 1c, 2a, 2b into classes - 2/5
			
	REPORT -
		Graph 1A vs 1B - 0/1
		Analysis 1A vs 1B - 0/1
	
		Graph 1C - 0/1
		Analysis 1C - 0/1

		Analysis 1B vs 1C - 0/1
		Graph 2A vs 2B - 0/1
		Analysis 2A vs 2B - 0/1

		Analysis 1 vs 2 - 0/1			
*/

#include <fstream>
#include <algorithm> //std::max
#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include "HashTable.h"
#include "Heap.h"
#include "DynamicKnapsack.h"

using matrix = std::vector<std::vector<int>>;
const int ALPHA = 4; // ask me about this 

struct Result {
    int basicOps;
    std::stack<int> optimalSet;
    int optimalValue;
};

//reads in the file and stores the contents in the vector
bool fileToVector(const std::string& filename, std::vector<int>& values){
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    int value;

    while (inputFile >> value){
        values.push_back(value);
    }

    inputFile.close();
    return true;
}

//recursive helper for space-efficient approach, builds the set of items that were chosen in the optimal solution of the knapsack problem
std::stack<int> optimalSetBuilderHash(std::stack<int>& set, int i, int j, const std::vector<int>& v, const std::vector<int>& w, HashTable& hashTable, int& opCount){
    //the basic operation is comparison, each call compares one pair of cells
    opCount++;
    if (i == 0 || j == 0){
        return set;
    }
    int currentValue = hashTable.lookup(i,j,opCount);
    int previousValue;

    if (i-1 == 0){
        previousValue = 0;
    } else {
        previousValue = hashTable.lookup(i-1,j,opCount);
    }

    if (currentValue > previousValue) {
        set.push(i);
        optimalSetBuilderHash(set, i-1, j-w[i-1], v, w, hashTable, opCount);
    }
    else {
        optimalSetBuilderHash(set,i-1,j,v,w,hashTable, opCount);
    }
    return set;
}

//Space-efficient Dynamic Programming
int spaceEfficientHelper(const std::vector<int>& v, const std::vector<int>& w, int i, int j, HashTable& hashTable, int& opCount){
    
    if (i == 0  || j == 0){
        return 0;
    }

    int stored = hashTable.lookup(i,j,opCount);
    
    if (stored != -1){
        return stored;
    }
    int solution;

    if (j < w[i-1]) {
        solution = spaceEfficientHelper(v,w,i-1,j,hashTable,opCount);
    } else {
        solution = std::max(spaceEfficientHelper(v, w, i-1, j, hashTable, opCount), v[i-1] + spaceEfficientHelper(v,w,i-1,j-w[i-1], hashTable, opCount));
    }

    hashTable.insert(i,j,solution,opCount);
    opCount++;
    return solution;
}

Result spaceEfficient(const std::vector<int>& v, const std::vector<int>& w, int W, int k){
    int opCount = 0;
    int n = static_cast<int>(v.size());
    std::stack<int> set;
    HashTable hashTable(k, W);
    Result result;

    result.optimalValue = spaceEfficientHelper(v,w,n,W,hashTable,opCount);
    result.optimalSet = optimalSetBuilderHash(set, n, W, v, w, hashTable, opCount);
    result.basicOps = opCount;

    return result;
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

Result greedyFunction(const std::vector<int>& v, const std::vector<int>& w, int capacity) {
    std::vector<std::pair<double, int>> ratioList(v.size());
    int opCount = 0;

    for (std::size_t i = 0; i < v.size(); i++) {
        opCount++;
        ratioList[i].first = static_cast<double>(v[i]) / w[i];
        ratioList[i].second = static_cast<int>(i);
    }

    if (!ratioList.empty()) {
        mergeSort(ratioList, 0, static_cast<int>(ratioList.size()) - 1, opCount);
    }
    else{
        Result out;
        out.basicOps = opCount;
        out.optimalSet = std::stack<int>();
        out.optimalValue = 0;

        return out;
    }

    std::stack<int> outputSet;
    int greedyValue = 0;
    int tempCapacity = capacity;

    for (std::size_t i = 0; i < ratioList.size() && tempCapacity > 0; i++) {
        int itemIndex = ratioList[i].second;

        opCount++; // counts one greedy item-fit check

        if (tempCapacity >= w[itemIndex]) {
            tempCapacity -= w[itemIndex];
            greedyValue += v[itemIndex];
            outputSet.push(itemIndex + 1);
        }
    }

    Result out;
    out.basicOps = opCount;
    out.optimalSet = outputSet;
    out.optimalValue = greedyValue;

    return out;
}

Result heapFunction(const std::vector<int>& v, const std::vector<int>& w, int capacity) {
    std::vector<std::pair<double, int>> ratioList(v.size());
    int opCount = 0;

    for (std::size_t i = 0; i < v.size(); i++) {
        opCount++;
        ratioList[i].first = static_cast<double>(v[i]) / w[i];
        ratioList[i].second = static_cast<int>(i);
    }
    heap h(ratioList);

    if (!ratioList.empty()) {
        opCount += h.getOpCount();
    } else {
        Result out;
        out.basicOps = opCount;
        out.optimalSet = std::stack<int>();
        out.optimalValue = 0;

        return out;
    }

    std::stack<int> outputSet;
    int greedyValue = 0;
    int tempCapacity = capacity;

    for (std::size_t i = 0; i < ratioList.size() && tempCapacity > 0; i++) {
        int itemIndex = h.extractMax().second;

        opCount++; // counts one greedy item-fit check

        if (tempCapacity >= w[itemIndex]) {
            tempCapacity -= w[itemIndex];
            greedyValue += v[itemIndex];
            outputSet.push(itemIndex + 1);
        }
    }

    Result out = Result();
    out.basicOps = opCount;
    out.optimalSet = outputSet;
    out.optimalValue = greedyValue;

    return out;
}

int main(int argc, char* argv[]) {
	
    //input handling
    if (argc != 2) {
	    std::cerr << "Incorrect input. Correct format: ./<exectuable.out> <filenumber>" << std::endl;
	    return 1;
	}
    
	std::string dataset = argv[1];
    std::string capacityFile;
    std::string valuesFile;
    std::string weightsFile ;

    if (dataset != "10") {
        capacityFile = "./KnapsackTestData/p0" + dataset + "_c.txt";
        valuesFile = "./KnapsackTestData/p0" + dataset + "_v.txt";
        weightsFile = "./KnapsackTestData/p0" + dataset + "_w.txt";
    } else {
        capacityFile = "./KnapsackTestData/p" + dataset + "_c.txt";
        valuesFile = "./KnapsackTestData/p" + dataset + "_v.txt";
        weightsFile = "./KnapsackTestData/p" + dataset + "_w.txt";
    }

    std::vector<int> capacity;    
    std::vector<int> values;
    std::vector<int> weights;

    if (!fileToVector(capacityFile, capacity)) {
		return 1;
	}
    if (!fileToVector(valuesFile, values)) { 
		return 1;
	}
    if (!fileToVector(weightsFile, weights)) { 
		return 1;
	}

    if (values.size() != weights.size()){
        std::cerr << "Weights and Values files are different sizes." << std::endl;
    }

    int W = capacity[0];
    int n = static_cast<int>(values.size());

    std::cout << "File containing the capacity, weights, and values are: " << capacityFile << ", " << weightsFile << ", " << valuesFile << std::endl << std::endl;
    std::cout << "Knapsack capacity = " << W << ". Total number of items = " << n << std::endl << std::endl;

    DynamicKnapsack tradKnapsack(values, weights, n, W);
    tradKnapsack.solveTraditional();
    tradKnapsack.printTradResult();

    DynamicKnapsack memKnapsack(values,weights,n,W);
    memKnapsack.solveMemoryFunction();
    memKnapsack.printMemoryResult();

    // space efficient dynamic programming
    int k = ((n * W) / ALPHA);
    Result spaceEfficientResult = spaceEfficient(values, weights, W, k);

    // greedy approach
    Result greedyResult = greedyFunction(values, weights, W);

    // heap based greedy approach
    Result heapResult = heapFunction(values, weights, W);

    //hash results
    std::cout << "(1c) Space-Efficient Dynamic Programming Optimal value: " << spaceEfficientResult.optimalValue <<std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Optimal subset: {";
    while (!spaceEfficientResult.optimalSet.empty()){
        std::cout << spaceEfficientResult.optimalSet.top();
        spaceEfficientResult.optimalSet.pop();
        if (!spaceEfficientResult.optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Total Basic Ops: " << spaceEfficientResult.basicOps << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Space Taken: " << k << std::endl << std::endl;

    //greedy results
    std::cout << "(2a) Greedy Approach Optimal value: " << greedyResult.optimalValue << std::endl;
    std::cout << "(2a) Greedy Approach Optimal subset: {";
    while (!greedyResult.optimalSet.empty()){
        std::cout << greedyResult.optimalSet.top();
        greedyResult.optimalSet.pop();
        if (!greedyResult.optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(2a) Greedy Approach Total Basic Ops: " << greedyResult.basicOps << std::endl << std::endl;

    //heap results
    std::cout << "(2b) Heap-based Greedy Approach Optimal value: " << heapResult.optimalValue << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Optimal subset: {";
    while (!heapResult.optimalSet.empty()){
        std::cout << heapResult.optimalSet.top();
        heapResult.optimalSet.pop();
        if (!heapResult.optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Total Basic Ops: " << heapResult.basicOps << std::endl << std::endl;

    return 0;
}

