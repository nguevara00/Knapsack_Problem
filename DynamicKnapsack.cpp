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

void DynamicKnapsack::printResult(){
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