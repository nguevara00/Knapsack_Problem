// Nick Guevara William Dappen
// CS 415 Gill
// Project 4 - Knapsack
// 5-9-2026

#include <fstream>
#include <algorithm> //std::max & std::sort for 2A & B output formatting
#include <vector>
#include <iostream>
#include <string>
#include <vector>

#include "HashTable.h"
#include "Heap.h"
#include "DynamicKnapsack.h"
#include "Utils.h"
#include "SpaceEfficient.h"
#include "Greedy.h"

const int ALPHA = 8; // tuning parameter for space vs time tradeoff in 1c hash table approach

void allToCSV(std::string dataset, DynamicKnapsack tradKnapsack, DynamicKnapsack memKnapsack, SpaceEfficient hashKnapsack, Greedy greedyKnapsack, Greedy heapKnapsack){
    std::string caseId = "p";

    if (dataset == "10") {
        caseId += "10";
    }
    else {
        caseId += "0" + dataset;
    }

    writeHeaderIfEmpty(
        "task1ab_results.csv",
        "1A vs 1B: Basic Ops by Case\ncase_id,approach,basic_ops,optimal_value"
    );

    appendCSVRow(
        "task1ab_results.csv",
        caseId + ",traditional_dp," +
        std::to_string(tradKnapsack.getBasicOps()) + "," +
        std::to_string(tradKnapsack.getOptimalValue())
    );

    appendCSVRow(
        "task1ab_results.csv",
        caseId + ",memory_function," +
        std::to_string(memKnapsack.getBasicOps()) + "," +
        std::to_string(memKnapsack.getOptimalValue())
    );

    writeHeaderIfEmpty(
    "task2_results.csv",
    "Task 2: Greedy Approaches\ncase_id,approach,basic_ops,optimal_value"
    );

    appendCSVRow(
        "task2_results.csv",
        caseId + ",greedy_sort," +
        std::to_string(greedyKnapsack.getBasicOps()) + "," +
        std::to_string(greedyKnapsack.getOptimalValue())
    );

    appendCSVRow(
        "task2_results.csv",
        caseId + ",greedy_heap," +
        std::to_string(heapKnapsack.getBasicOps()) + "," +
        std::to_string(heapKnapsack.getOptimalValue())
    );

    writeHeaderIfEmpty(
    "task1_vs_task2_results.csv",
    "1 vs 2: Basic Ops by Case\ncase_id,approach,basic_ops,optimal_value"
    );

    appendCSVRow(
        "task1_vs_task2_results.csv",
        caseId + ",memory_function," +
        std::to_string(memKnapsack.getBasicOps()) + "," +
        std::to_string(memKnapsack.getOptimalValue())
    );

    appendCSVRow(
        "task1_vs_task2_results.csv",
        caseId + ",greedy_heap," +
        std::to_string(heapKnapsack.getBasicOps()) + "," +
        std::to_string(heapKnapsack.getOptimalValue())
    );

}


int excecuteAll(std::string dataset, bool writeToCSV, bool printResults = false)
{
    std::string capacityFile;
    std::string valuesFile;
    std::string weightsFile ;

    if (stoi(dataset) < 10) {
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

    //initialize parameters from input
    int W = capacity[0];
    int n = static_cast<int>(values.size());
    int k = ((n * W) / ALPHA);

    if(printResults){
        //print input stats
        std::cout << "File containing the capacity, weights, and values are: " << capacityFile << ", " << weightsFile << ", " << valuesFile << std::endl << std::endl;
        std::cout << "Knapsack capacity = " << W << ". Total number of items = " << n << std::endl << std::endl;
    }
    //solve the knapsack

    // traditional dynamic programming
    DynamicKnapsack tradKnapsack(values, weights, n, W);
    tradKnapsack.solveTraditional();
    if (printResults)
    {
        tradKnapsack.printTradResult();
    }

    // memory function dynamic programming
    DynamicKnapsack memKnapsack(values, weights, n, W);
    memKnapsack.solveMemoryFunction();
    if (printResults)
    {
        memKnapsack.printMemoryResult();
    }

    // space efficient dynamic programming
    SpaceEfficient hashKnapsack(values, weights, n, W, k);
    hashKnapsack.solveSpaceEfficient();
    if (printResults)
    {  
        hashKnapsack.printSpaceResult();
    }
    // greedy approach
    Greedy greedyKnapsack(values, weights, n, W);
    greedyKnapsack.solveGreedy();
    if (printResults)
    {
        greedyKnapsack.printGreedyResults();
    }

    // heap based greedy approach
    Greedy heapKnapsack(values, weights, n, W);
    heapKnapsack.solveHeap();
    if (printResults)
    {
        heapKnapsack.printHeapResults();
    }

    if(writeToCSV){
        allToCSV(dataset, tradKnapsack, memKnapsack, hashKnapsack, greedyKnapsack, heapKnapsack);
    }
    return 0;
}

int main(int argc, char* argv[]) {
	emptyFile("task1ab_results.csv");
    emptyFile("task2_results.csv");
    emptyFile("task1_vs_task2_results.csv");

    //input handling
    if (argc != 2) {
	    std::cerr << "Incorrect input. Correct format: ./<exectuable.out> <filenumber>" << std::endl;
	    return 1;
	}
    
	std::string dataset = argv[1];
    // execute all algorithms for the given dataset, print results, but dont write to csv
    excecuteAll(dataset, false, true);
    for(int i = 1; i <= 8; i++){  // Assuming there are 10 datasets
        std::string dataset = std::to_string(i);
        // execute all algorithms for the given dataset (i), dont print the results but write to csv
        excecuteAll(dataset, true);
    }
    return 0;
}

