#include "DynamicKnapsack.h"
#include <algorithm> //std max

void DynamicKnapsack::optimalSetBuilder(int i, int j, const matrix& solutionGrid){
    //the basic operation is comparison, each call compares one pair of cells
    basicOps++;
    if (i == 0 || j == 0){
        return;
    }
    else if (solutionGrid[i][j] > solutionGrid[i-1][j]) {
        this->optimalSet.push(i);
        optimalSetBuilder(i-1, j- this->w[i-1], solutionGrid);
    }
    else {
        optimalSetBuilder(i-1,j,solutionGrid);
    }
    return;
}

void DynamicKnapsack::solveTraditional(){
    matrix solutionGrid(n + 1, std::vector<int>(W + 1, 0));

    // fill the cells and count the basic operations.
    // define 1 basic operation as filling a cell, since each branch of the loop does this in constant time. 
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= W; j++){
            basicOps++;
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
    optimalValue = solutionGrid[n][W];
    optimalSetBuilder(n, W, solutionGrid);     
}

void DynamicKnapsack::printTradResult(){
    //trad results
    std::cout << "(1a) Traditional Dynamic Programming Optimal value: " << optimalValue << std::endl;
    std::cout << "(1a) Traditional Dynamic Programming Optimal subset: {";
    while (!optimalSet.empty()){
        std::cout << optimalSet.top();
        optimalSet.pop();
        if (!optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(1a) Traditional Dynamic Programming Total Basic Ops: " << basicOps << std::endl << std::endl;
}

void DynamicKnapsack::printMemoryResult(){
    //mem results
    std::cout << "(1b) Memory-function Dynamic Programming Optimal value: " << optimalValue << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Optimal subset: {";
     while (!optimalSet.empty()){
        std::cout << optimalSet.top();
        optimalSet.pop();
        if (!optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Total Basic Ops: " << basicOps << std::endl << std::endl;
}




//Built off of the traditional dynamic programming approach, fills the solution matrix for the knapsack problem from both ends
// assume solutionGrid is initialized to -1 for all cells, so that we can check if a cell has been filled or not
// Recursive function, therefore memoryFunction() will be a shell around a recursive helper function that fills the solution grid
void DynamicKnapsack::solveMemoryFunction(){

    matrix solutionGrid(n + 1, std::vector<int>(W + 1, -1));
    memoryHelper(n, W, solutionGrid);
    optimalSetBuilder(n, W, solutionGrid);
    optimalValue = solutionGrid[n][W];
}

int DynamicKnapsack::memoryHelper(int i, int j, matrix& solutionGrid){
    // added base case, first rows and columns must be zero
    if (i == 0 || j == 0) {
        if (solutionGrid[i][j] == -1) {
            solutionGrid[i][j] = 0;
            basicOps++;
        }
        return solutionGrid[i][j];
    }

    if (solutionGrid[i][j] != -1) {
        return solutionGrid[i][j];
    }

    basicOps++;

    if (j < w[i - 1]) {
        solutionGrid[i][j] = memoryHelper(i - 1, j, solutionGrid);
    } else {
        int exclude = memoryHelper(i - 1, j, solutionGrid);
        int include = v[i - 1] + memoryHelper(i - 1, j - w[i - 1], solutionGrid);

        solutionGrid[i][j] = std::max(exclude, include);
    }

    return solutionGrid[i][j];
}

