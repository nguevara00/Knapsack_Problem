#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <stack>

class Greedy{
    private:
        int n;
        int W;
        std::vector<int> v;
        std::vector<int> w;

        std::stack<int> optimalSet;
        int optimalValue;
        int basicOps;
        
    
    public:
        Greedy(const std::vector<int>& v, const std::vector<int>& w, const int& n, const int& W){
            this->n = n;
            this->W = W;
            this->v = v;
            this->w = w;
        }
        void solveGreedy();
        void solveHeap();
        void printGreedyResults();
        void printHeapResults();

};
#endif