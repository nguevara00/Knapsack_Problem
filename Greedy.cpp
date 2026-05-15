#include "Greedy.h"
#include <utility>
#include "Utils.h"
#include "Heap.h"
#include <iostream>
#include <algorithm>

void Greedy::solveGreedy() {
    std::vector<std::pair<double, int>> ratioList(n);
    int tempCapacity = W;

    // Reset results in case this object is reused
    basicOps = 0;
    optimalValue = 0;
    optimalSet = std::stack<int>();

    for (std::size_t i = 0; i < v.size(); i++) {
        basicOps++; // ratio computation
        ratioList[i].first = static_cast<double>(v[i]) / w[i];
        ratioList[i].second = static_cast<int>(i);
    }

    if (!ratioList.empty()) {
        mergeSort(ratioList, 0, static_cast<int>(ratioList.size()) - 1, basicOps);
    }
    else {
        optimalValue = 0;
        return;
    }

    int greedyValue = 0;

    for (std::size_t i = 0; i < ratioList.size() && tempCapacity > 0; i++) {
        int itemIndex = ratioList[i].second;

        basicOps++; // greedy capacity check

        if (tempCapacity >= w[itemIndex]) {
            tempCapacity -= w[itemIndex];
            greedyValue += v[itemIndex];
            optimalSet.push(itemIndex + 1);
        }
        else {
            break; // assignment says stop after first item that does not fit
        }
    }

    optimalValue = greedyValue;
}

void Greedy::solveHeap() {
    std::vector<std::pair<double, int>> ratioList(n);

    // Reset results in case this object is reused
    basicOps = 0;
    optimalValue = 0;
    optimalSet = std::stack<int>();

    for (std::size_t i = 0; i < v.size(); i++) {
        basicOps++; // ratio computation
        ratioList[i].first = static_cast<double>(v[i]) / w[i];
        ratioList[i].second = static_cast<int>(i);
    }

    if (ratioList.empty()) {
        optimalValue = 0;
        return;
    }

    heap h(ratioList);

    int greedyValue = 0;
    int tempCapacity = W;

    for (std::size_t i = 0; i < ratioList.size() && tempCapacity > 0; i++) {
        int itemIndex = h.extractMax().second;

        basicOps++; // greedy capacity check

        if (tempCapacity >= w[itemIndex]) {
            tempCapacity -= w[itemIndex];
            greedyValue += v[itemIndex];
            optimalSet.push(itemIndex + 1);
        }
        else {
            break; // assignment says stop after first item that does not fit
        }
    }

    basicOps += h.getOpCount(); // heap build + all deleteMax heapifyDown comparisons
    optimalValue = greedyValue;
}

void Greedy::printGreedyResults() {
    std::vector<int> outputArray;

    std::cout << "(2a) Greedy Approach Optimal value: " << optimalValue << std::endl;
    std::cout << "(2a) Greedy Approach Optimal subset: {";

    while (!optimalSet.empty()) {
        outputArray.push_back(optimalSet.top());
        optimalSet.pop();
    }

    std::sort(outputArray.begin(), outputArray.end());

    for (std::size_t i = 0; i < outputArray.size(); i++) {
        std::cout << outputArray[i];
        if (i < outputArray.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "}" << std::endl;
    std::cout << "(2a) Greedy Approach Total Basic Ops: " << basicOps << std::endl << std::endl;
}

void Greedy::printHeapResults() {
    std::vector<int> outputArray;

    std::cout << "(2b) Heap-based Greedy Approach Optimal value: " << optimalValue << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Optimal subset: {";

    while (!optimalSet.empty()) {
        outputArray.push_back(optimalSet.top());
        optimalSet.pop();
    }

    std::sort(outputArray.begin(), outputArray.end());

    for (std::size_t i = 0; i < outputArray.size(); i++) {
        std::cout << outputArray[i];
        if (i < outputArray.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "}" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Total Basic Ops: " << basicOps << std::endl << std::endl;
}