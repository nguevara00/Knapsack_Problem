#ifndef SPACEEFFICIENT_H
#define SPACEEFFICIENT_H

#include <vector>
#include <stack>
#include "HashTable.h"


class SpaceEfficient{
    private:
        int n;
        int W;
        int k;
        std::vector<int> v;
        std::vector<int> w;

        std::stack<int> optimalSet;
        int optimalValue;
        int basicOps;

        void optimalSetBuilderHash(int i, int j, HashTable& hashTable);
        int spaceEfficientHelper(int i, int j, HashTable& hashTable);
    
    public:
        SpaceEfficient(const std::vector<int>& v, const std::vector<int>& w, const int& n, const int& W, const int& k){
            this->n = n;
            this->W = W;
            this->v = v;
            this->w = w;
            this->k = k;
            basicOps = 0;
            optimalValue = 0;
        }

        void solveSpaceEfficient();
        void printSpaceResult();

        
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
