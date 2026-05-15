#ifndef DYNAMIC_KNAPSACK_H
#define DYNAMIC_KNAPSACK_H

#include <vector>
#include <stack>
#include <iostream>

using matrix = std::vector<std::vector<int>>;

class DynamicKnapsack{
private:
    int n;
    int W;
    std::vector<int> v;
    std::vector<int> w;

    std::stack<int> optimalSet;
    int optimalValue;
    int basicOps;
    void optimalSetBuilder(int i, int j, const matrix& solutionGrid);
    int memoryHelper(int i, int j, matrix& solutionGrid);
    
public:
    DynamicKnapsack(const std::vector<int>& v, const std::vector<int>& w, const int& n, const int& W){
        this->n = n;
        this->W = W;
        this->v = v;
        this->w = w;
    }

    void solveTraditional();
    void printTradResult();
    
    void solveMemoryFunction();
    void printMemoryResult();

    auto getOptimalValue() const {
        return optimalValue;
    }
    auto getBasicOps() const {
        return basicOps;
    }
    auto getOptimalSet() const {
        return optimalSet;
    }
};

#endif