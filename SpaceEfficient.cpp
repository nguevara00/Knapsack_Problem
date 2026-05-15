#include "SpaceEfficient.h"
#include "HashTable.h"
#include <algorithm>
#include <iostream>

//recursive helper for space-efficient approach, builds the set of items that were chosen in the optimal solution of the knapsack problem
void SpaceEfficient::optimalSetBuilderHash(int i, int j, HashTable& hashTable){
    //the basic operation is comparison, each call compares one pair of cells
    basicOps++;
    if (i == 0 || j == 0){
        return;
    }
    int currentValue = hashTable.lookup(i,j,basicOps);
    int previousValue;

    if (i-1 == 0){
        previousValue = 0;
    } else {
        previousValue = hashTable.lookup(i-1,j,basicOps);
    }

    if (currentValue > previousValue) {
        optimalSet.push(i);
        optimalSetBuilderHash(i-1, j-w[i-1],hashTable);
    }
    else {
        optimalSetBuilderHash(i-1,j,hashTable);
    }
}

//Space-efficient Dynamic Programming
int SpaceEfficient::spaceEfficientHelper(int i, int j, HashTable& hashTable){
    
    if (i == 0  || j == 0){
        return 0;
    }

    int stored = hashTable.lookup(i,j,basicOps);
    
    if (stored != -1){
        return stored;
    }
    int solution;

    if (j < w[i-1]) {
        solution = spaceEfficientHelper(i-1,j,hashTable);
    } else {
        solution = std::max(spaceEfficientHelper(i-1, j, hashTable), v[i-1] + spaceEfficientHelper(i-1,j-w[i-1], hashTable));
    }

    hashTable.insert(i,j,solution,basicOps);
    basicOps++;
    return solution;
}

void SpaceEfficient::solveSpaceEfficient(){
    HashTable hashTable(k, W);
    optimalValue = spaceEfficientHelper(n,W,hashTable);
    optimalSetBuilderHash(n, W, hashTable);
}

void SpaceEfficient::printSpaceResult(){
    //hash results
    std::cout << "(1c) Space-Efficient Dynamic Programming Optimal value: " << optimalValue <<std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Optimal subset: {";
    while (!optimalSet.empty()){
        std::cout << optimalSet.top();
        optimalSet.pop();
        if (!optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Total Basic Ops: " << basicOps << std::endl;
    std::cout << "(1c) Space-Efficient Dynamic Programming Space Taken: " << k << std::endl << std::endl;
}
