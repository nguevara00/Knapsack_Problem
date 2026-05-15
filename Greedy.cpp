#include "Greedy.h"
#include <utility>
#include "Utils.h"
#include "Heap.h"
#include <iostream>

void Greedy::solveGreedy() {
    std::vector<std::pair<double, int>> ratioList(n);
    int tempCapacity = W;

    for (std::size_t i = 0; i < v.size(); i++) {
        basicOps++;
        ratioList[i].first = static_cast<double>(v[i]) / w[i];
        ratioList[i].second = static_cast<int>(i);
    }

    if (!ratioList.empty()) {
        mergeSort(ratioList, 0, static_cast<int>(ratioList.size()) - 1, basicOps);
    }
    else{
        optimalSet = std::stack<int>();
        optimalValue = 0;
        return;
    }

    int greedyValue = 0;
    for (std::size_t i = 0; i < ratioList.size() && tempCapacity > 0; i++) {
        int itemIndex = ratioList[i].second;

        basicOps++; // counts one greedy item-fit check

        if (tempCapacity >= w[itemIndex]) {
            tempCapacity -= w[itemIndex];
            greedyValue += v[itemIndex];
            optimalSet.push(itemIndex + 1);
        }
    }
    optimalValue = greedyValue;
    return;
}

void Greedy::solveHeap() {
    std::vector<std::pair<double, int>> ratioList(n);

    for (std::size_t i = 0; i < v.size(); i++) {
        basicOps++;
        ratioList[i].first = static_cast<double>(v[i]) / w[i];
        ratioList[i].second = static_cast<int>(i);
    }

    heap h(ratioList);

    if (!ratioList.empty()) {
        basicOps += h.getOpCount();
    } else {
        return;
    }

    int greedyValue = 0;
    int tempCapacity = W;

    for (std::size_t i = 0; i < ratioList.size() && tempCapacity > 0; i++) {
        int itemIndex = h.extractMax().second;

        basicOps++; // counts one greedy item-fit check

        if (tempCapacity >= w[itemIndex]) {
            tempCapacity -= w[itemIndex];
            greedyValue += v[itemIndex];
            optimalSet.push(itemIndex + 1);
        }
    }
    optimalValue = greedyValue;
    return;
}

void Greedy::printGreedyResults(){
    //greedy results
    std::cout << "(2a) Greedy Approach Optimal value: " << optimalValue << std::endl;
    std::cout << "(2a) Greedy Approach Optimal subset: {";
    while (!optimalSet.empty()){
        std::cout << optimalSet.top();
        optimalSet.pop();
        if (!optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(2a) Greedy Approach Total Basic Ops: " << basicOps << std::endl << std::endl;
}

void Greedy::printHeapResults(){
    std::cout << "(2b) Heap-based Greedy Approach Optimal value: " << optimalValue << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Optimal subset: {";
    while (!optimalSet.empty()){
        std::cout << optimalSet.top();
        optimalSet.pop();
        if (!optimalSet.empty()){
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Total Basic Ops: " << basicOps << std::endl << std::endl;
}
