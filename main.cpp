// Nick Guevara William Dappen
// CS 415 Gill
// Project 4 - Knapsack
// 5-9-2026


// AI is specifically instructed not to provide any C++ code

// permissible AI: 
// forguidance or refresher on algorithms. pseudocode only, for implementation of algorithms and data structure, and hash functions. 
// for debugging. do not provide solution only point to potential issues. each use in this way must be reported. Use only as a peer reviewer, not solution generator.
// for refactoring code
// for doing tasks not related to algorithms, such as code for generating graphs and reading files.
// for generating data sets
// tasks supporting extra credit portion

// Goals: Solve the knapsack problem using the traditional and "memory function" approach of dynamic programming.
//          Compare and contrast these with a space-efficient variant where the values are not stored in a 2D table but in a hash table
//        Solve the knapsack problem using the greedy approach
//          Compare and contrast with a heap-based implementation of the greedy approach.
//        Describe your use of AI in the understanding and implementation of this project
//        Extend the scope of the project in the form of an application or improvement in the method code or design


// Input: Given n items and corresponding value vector v1, v2, ..., vn and the weight vector w1, w2, ..., wn. Let W = capacity of the knapsack. 


// TASK 1A : Traditional Dynamic Programming Approach
// Implement dynamic programming based algorithm to determine the optimal value of the knapsack and the set of items that yield this optimal value.    
// This requires filling all the cells in the (n x W) table
// Display the optimal value F(n, W), subset yielding the optimal value, and the number of basic operations (for finding both the optimal value and optimal subset).
// Note, items begin with index 1 and so the set of all items = {1, 2, 3, ...., n}. (see sample output below)


// TASK 1B : Memory Function based Dynamic Programming Approach
// Implement dynamic programming based on the memory function (page 295 of the textbook) to determine the optimal value of the knapsack and the set of items that yield this optimal value.
// This requires filling a subset of cells in the (n x W) table
// Display the optimal value F(n, W), subset yielding the optimal value, and the number of basic operations (for finding both the optimal value and optimal subset). 
// Note, items begin with index 1 and so the set of all items = {1, 2, 3, ...., n}. (see sample output below)


// TASK 1C : Space-efficient approach using hash tables
// Even though the approach in Task 1b does not fill all cells of the n x W table, it requires O(nW) space to allocate the 2D table. For sufficiently large values of nW (say ~ 1 billion), your computer may run out of memory. 
// For this task, we will use an alternative method that will use less space but may use more time to find the optimal values.
//    Implement dynamic programming based on the memory function (page 295 of the textbook) to determine the optimal value of the knapsack and the set of items that yield this optimal value.
//    Instead of storing the values of F(i, j) in an (n x W) table, use an open hash table with k cells and a hash function h(i, j) that depends on both i and j.
//        Resolve collisions using open hashing (also known as separate-chaining), where the keys (i, j) and value F(i, j) are stored in a linear linked list.
//    Choose h(i, j) in the following (vanilla) way:
//        Create a mapping from the pair (i, j) to an integer (i-1)*W + j  (where 1 <= j <= W , and 1 <= i <= n)
//        Take a modulus with k (so that the hash value fits in a hash table with k cells)
//        Taking the two points together, h(i , j) =  [ (i-1)*W + j ] mod k.  
//    Strategically determine the values of k so that collisions are minimized but the space used (size of the entire hash table) is significantly smaller than nW. Use the test data p08 for this purpose
//    (because the capacity W in other data files is too small to make a noticeable difference). You are also permitted to generate new data sets for testing.
//    Display the optimal value, subset yielding the optimal value, and the number of basic operations (for finding both the optimal value and optimal subset). Note, items begin with index 1 and so the set of all items = {1, 2, 3, ...., n}     
// See additonal requirements for report


// TASK 2A: Greedy approach using sorting
// Implement a greedy algorithm that arranges the items in the decreasing order of value to weight ratio (vi/wi for i = 1, 2, ..., n), then select the items in this order until the weight of the next item exceeds the remaining capacity (Note: In this greedy version, we stop right after the first item whose inclusion would exceed the knapsack capacity).
//    To sort the items, implement a Theta(n log n) sorting method of your choice (Do not use inbuilt sort as we need to compute the total number of basic operations).
// Display the best value, subset yielding the best value, and the total number of basic operations (includes operations for sorting, finding the best value, and the corresponding subset). 
// Note, items begin with index 1 and so the set of all items = {1, 2, 3, ...., n}. (see sample output below)


// TASK 2B : Greedy Approach using max-heap
// Implement the greedy algorithm based on a max-heap that supports the operation deletemax.
// The idea is to use the O(n) algorithm (bottom-up approach) to build the heap containing the n keys (vi/wi for i = 1, 2, ..., n) then perform a series of deletemax. 
// If the number of objects that are selected by the greedy algorithm is k, then the total complexity is O(n + k log n) which could be better than O(n log n) in some cases (the complexity of best sorting algorithm).
// Display the best value, subset yielding the best value, and the total number of basic operations (includes operations for building the heap, finding the best value, and the corresponding subset). 
// Note, items begin with index 1 and so the set of all items = {1, 2, 3, ...., n}

/* TASK 3 : Comparison for report

Task 1a vs Task 1b:
    Produce a graph that compares the total number of basic operations taken by the traditional and "memory-function" approaches (1a and 1b) for all the input cases. Note: the x-axis is case-id and the y-axis is the number of operations.
        You may (and are encouraged) to use different input files that can help in supporting your argument.
    Comment on which approach is more efficient and why?

Task 1c: 

    Using a graph, compare the time (number of basic Ops) and the space taken by approach 1c for different values of k. Note: x-axis is space (k) and y-axis is time (number of basic ops).
        You may (and are encouraged) to use different input files that can help in supporting your argument.
    Compare the performance of two hash functions. Which one is better?

Task 1b vs Task 1c:

    Discuss how the optimal value of k was determined such that collisions are minimized but the space used is significantly smaller than nW?
    Comment on the advantages/disadvantages of approach 1b vs 1c.

Task 2:

    Produce a graph that compares the total number of basic operations taken by greedy approaches (2a and 2b) for all the input cases. Note: x-axis is case-id and the y-axis is number of operations.
        You may (and are encouraged) to use different input files that can help in supporting your argument.
    Comment on which approach is more efficient and why? 

Task 1 vs Task 2:

    Using a suitable algorithm from Task 1 and Task 2, compare and contrast the time taken by these two algorithms and the optimal value they generate.
        You may (and are encouraged) to use different input files that can help in supporting your argument.
    Which algorithm would you pick, given what you have learned in this project? Why?

Task Tracking -

	PROGRAMMING -
		1A - 3/3
		1B - 0/3
		1C - 0/4
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
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using matrix = std::vector<std::vector<int>>;

struct Result {
    int basicOps;
    std::vector<int> optimalSet;
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

//recursive helper for traditionalDynamic, builds the set of items that were chosen in the optimal solution of the knapsack problem
std::vector<int> optimalSetBuilder(std::vector<int>& set, int i, int j, const std::vector<int>& v, const std::vector<int>& w, const matrix& solutionGrid, int& opCount){
    // what is the basic operation??
    // we say its comparison and each call compares a pair of cells once
    opCount++;
    if (i == 0 || j == 0){
        return set;
    }
    else if (solutionGrid[i][j] > solutionGrid[i-1][j]) {
        set.push_back(i);
        optimalSetBuilder(set, i-1, j-w[i-1], v, w, solutionGrid, opCount);
    }
    else {
        optimalSetBuilder(set,i-1,j,v,w,solutionGrid, opCount);
    }
    std::sort(set.begin(), set.end());
    return set;
}

//traditional dynamic programming, fills the solution matrix for the knapsack problem
Result traditionalDynamic(const std::vector<int>& v, const std::vector<int>& w, int W, matrix& solutionGrid){
    int opCount = 0;
    std::vector<int> set;
    Result result;
    
    // fill the cells and count the basic operations.
    // define 1 basic operation as filling a cell, since each branch of the loop does this in constant time. 
    for (size_t i = 0; i <= v.size(); i++){
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
    
    result.optimalSet = optimalSetBuilder(set, v.size(), W, v, w, solutionGrid, opCount); 
    result.basicOps = opCount;
    return result;
}





int main(int argc, char* argv[]) {
	
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
    int n = values.size();

    // traditional dynamic programming
    matrix solutionGrid(n + 1, std::vector<int>(W + 1, 0));
    Result traditionalResult = traditionalDynamic(values, weights, W, solutionGrid);

    // memory function dynamic programming
    //      not yet implemented

    // space efficient dynamic programming
    //      not yet implemented

    // greedy approach
    //      not yet implemented
    
    // heap based greedy approach
    //      not yet implemented



    //output section
    std::cout << "File containing the capacity, weights, and values are: " << capacityFile << ", " << weightsFile << ", " << valuesFile << std::endl << std::endl;
    std::cout << "Knapsack capacity = " << W << ". Total number of items = " << n << std::endl << std::endl;
    
    std::cout << "(1a) Traditional Dynamic Programming Optimal value: " << solutionGrid[values.size()][W] << std::endl;
    std::cout << "(1a) Traditional Dynamic Programming Optimal subset: {";
    for (size_t i = 0; i < traditionalResult.optimalSet.size(); i++){
        std::cout << traditionalResult.optimalSet[i];
        if (i != traditionalResult.optimalSet.size() - 1){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    
    std::cout << "(1a) Traditional Dynamic Programming Total Basic Ops: " << traditionalResult.basicOps << std::endl << std::endl;


    std::cout << "(1b) Memory-function Dynamic Programming Optimal value: not yet implemented" << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Optimal subset: not yet implemented" << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Total Basic Ops: not yet implemented" << std::endl << std::endl;

    std::cout << "(1c) Space-Efficient Dynamic Programming Optimal value: not yet implemented" << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Optimal subset: not yet implemented" << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Total Basic Ops: not yet implemented" << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Space Taken: not yet implemented" << std::endl << std::endl;

    std::cout << "(2a) Greedy Approach Optimal value: not yet implemented" << std::endl;
    std::cout << "(2a) Greedy Approach Optimal subset: not yet implemented" << std::endl;
    std::cout << "(2a) Greedy Approach Total Basic Ops: not yet implemented" << std::endl << std::endl;

    std::cout << "(2b) Heap-based Greedy Approach Optimal value: not yet implemented" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Optimal subset: not yet implemented" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Total Basic Ops: not yet implemented" << std::endl;

    return 0;
}

