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
#include <iostream>
#include <string>
#include <vector>

#include "HashTable.h"
#include "Heap.h"
#include "DynamicKnapsack.h"
#include "Utils.h"
#include "SpaceEfficient.h"
#include "Greedy.h"

const int ALPHA = 4; // ask me about this 

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
    Greedy greedyKnapsack(values, weights, n, W);
    greedyKnapsack.greedyFunction();
    greedyKnapsack.greedyPrintResults();

    // heap based greedy approach
    Greedy heapKnapsack(values, weights, n, W);
    heapKnapsack.heapFunction();
    heapKnapsack.heapPrintResults();    

    return 0;
}

