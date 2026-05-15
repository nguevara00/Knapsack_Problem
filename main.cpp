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
#include "Utils.h"
#include "SpaceEfficient.h"

const int ALPHA = 4; // ask me about this 

struct Result {
    int basicOps;
    std::stack<int> optimalSet;
    int optimalValue;
};


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
    int k = ((n * W) / ALPHA);

    std::cout << "File containing the capacity, weights, and values are: " << capacityFile << ", " << weightsFile << ", " << valuesFile << std::endl << std::endl;
    std::cout << "Knapsack capacity = " << W << ". Total number of items = " << n << std::endl << std::endl;

    // traditional dynamic programming
    DynamicKnapsack tradKnapsack(values, weights, n, W);
    tradKnapsack.solveTraditional();
    tradKnapsack.printTradResult();

    // memory function dynamic programming
    DynamicKnapsack memKnapsack(values, weights, n, W);
    memKnapsack.solveMemoryFunction();
    memKnapsack.printMemoryResult();

    // space efficient dynamic programming
    SpaceEfficient hashKnapsack(values, weights, n, W, k);
    hashKnapsack.solveSpaceEfficient();
    hashKnapsack.printSpaceResult();

    // greedy approach
    Result greedyResult = greedyFunction(values, weights, W);

    // heap based greedy approach
    Result heapResult = heapFunction(values, weights, W);

    

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

