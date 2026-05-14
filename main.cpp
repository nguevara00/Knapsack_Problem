// Nick Guevara William Dappen
// CS 415 Gill
// Project 4 - Knapsack
// 5-9-2026

/*
Task Tracking -

	PROGRAMMING -
		1A - 3/3
		1B - 3/3
		1C - 3/4
		2A - 0/3
		2B - 0/3
			
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

//recursive helper for dynamic programming approaches, builds the set of items that were chosen in the optimal solution of the knapsack problem
std::stack<int> optimalSetBuilder(std::stack<int>& set, int i, int j, const std::vector<int>& v, const std::vector<int>& w, const matrix& solutionGrid, int& opCount){
    //the basic operation is comparison, each call compares one pair of cells
    opCount++;
    if (i == 0 || j == 0){
        return set;
    }
    else if (solutionGrid[i][j] > solutionGrid[i-1][j]) {
        set.push(i);
        optimalSetBuilder(set, i-1, j-w[i-1], v, w, solutionGrid, opCount);
    }
    else {
        optimalSetBuilder(set,i-1,j,v,w,solutionGrid, opCount);
    }
    return set;
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

//traditional dynamic programming, fills the solution matrix for the knapsack problem
Result traditionalDynamic(const std::vector<int>& v, const std::vector<int>& w, int W){
    
    int opCount = 0;
    std::stack<int> set;
    Result result;
    int n = static_cast<int>(v.size());
    matrix solutionGrid(n + 1, std::vector<int>(W + 1, 0));
    
    // fill the cells and count the basic operations.
    // define 1 basic operation as filling a cell, since each branch of the loop does this in constant time. 
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= W; j++){
            opCount++;
            if (i == 0 || j == 0){
                solutionGrid[i][j] = 0;
            }

            else if (j - w[i-1] >= 0) {
                solutionGrid[i][j] = std::max(solutionGrid[i-1][j], v[i-1] + solutionGrid[i-1][j-w[i-1]]);
            }
            else {
                solutionGrid[i][j] = solutionGrid[i-1][j];
            }   
        }
    }
    
    result.optimalSet = optimalSetBuilder(set, n, W, v, w, solutionGrid, opCount); 
    result.basicOps = opCount;
    result.optimalValue = solutionGrid[n][W];

    return result;
}

//Built off of the traditional dynamic programming approach, fills the solution matrix for the knapsack problem from both ends
// assume solutionGrid is initialized to -1 for all cells, so that we can check if a cell has been filled or not
// Recursive function, therefore memoryFunction() will be a shell around a recursive helper function that fills the solution grid
int memoryHelper(const std::vector<int>& v, const std::vector<int>& w, int i, int j, matrix& solutionGrid, int& opCount){
    // added base case, first rows and columns must be zero
    if (i == 0 || j == 0) {
        if (solutionGrid[i][j] == -1) {
            solutionGrid[i][j] = 0;
            opCount++;
        }
        return solutionGrid[i][j];
    }

    if (solutionGrid[i][j] != -1) {
        return solutionGrid[i][j];
    }

    opCount++;

    if (j < w[i - 1]) {
        solutionGrid[i][j] = memoryHelper(v, w, i - 1, j, solutionGrid, opCount);
    } else {
        int exclude = memoryHelper(v, w, i - 1, j, solutionGrid, opCount);
        int include = v[i - 1] + memoryHelper(v, w, i - 1, j - w[i - 1], solutionGrid, opCount);

        solutionGrid[i][j] = std::max(exclude, include);
    }

    return solutionGrid[i][j];
}

Result memoryFunction(const std::vector<int>& v, const std::vector<int>& w, int W){
    int opCount = 0;
    int n = static_cast<int>(v.size());
    matrix solutionGrid(n + 1, std::vector<int>(W + 1, -1));
    memoryHelper(v, w, n, W, solutionGrid, opCount);
    std::stack<int> set;
    Result result;

    result.optimalSet = optimalSetBuilder(set, n, W, v, w, solutionGrid, opCount);
    result.basicOps = opCount;
    result.optimalValue = solutionGrid[n][W];

    return result;
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

    hashTable.insert(i,j,solution);
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
    // traditional dynamic programming
    Result traditionalDynamicResult = traditionalDynamic(values, weights, W);

    // memory function dynamic programming
    Result memoryFunctionResult = memoryFunction(values, weights, W);

    // space efficient dynamic programming
    int k = ((n * W) / ALPHA);
    Result spaceEfficientResult = spaceEfficient(values, weights, W, k);

    // greedy approach
    //      not yet implemented
    
    // heap based greedy approach
    //      not yet implemented



    //output section
    std::cout << "File containing the capacity, weights, and values are: " << capacityFile << ", " << weightsFile << ", " << valuesFile << std::endl << std::endl;
    std::cout << "Knapsack capacity = " << W << ". Total number of items = " << n << std::endl << std::endl;
    

    //trad results
    std::cout << "(1a) Traditional Dynamic Programming Optimal value: " << traditionalDynamicResult.optimalValue << std::endl;
    std::cout << "(1a) Traditional Dynamic Programming Optimal subset: {";
    while (!traditionalDynamicResult.optimalSet.empty()){
        std::cout << traditionalDynamicResult.optimalSet.top();
        traditionalDynamicResult.optimalSet.pop();
        if (!traditionalDynamicResult.optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(1a) Traditional Dynamic Programming Total Basic Ops: " << traditionalDynamicResult.basicOps << std::endl << std::endl;

    //mem results
    std::cout << "(1b) Memory-function Dynamic Programming Optimal value: " << memoryFunctionResult.optimalValue << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Optimal subset: {";
     while (!memoryFunctionResult.optimalSet.empty()){
        std::cout << memoryFunctionResult.optimalSet.top();
        memoryFunctionResult.optimalSet.pop();
        if (!memoryFunctionResult.optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Total Basic Ops: " << memoryFunctionResult.basicOps << std::endl << std::endl;


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
    std::cout << "(2a) Greedy Approach Optimal value: not yet implemented" << std::endl;
    std::cout << "(2a) Greedy Approach Optimal subset: not yet implemented" << std::endl;
    std::cout << "(2a) Greedy Approach Total Basic Ops: not yet implemented" << std::endl << std::endl;

    //heap results
    std::cout << "(2b) Heap-based Greedy Approach Optimal value: not yet implemented" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Optimal subset: not yet implemented" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Total Basic Ops: not yet implemented" << std::endl << std::endl;

    return 0;
}

