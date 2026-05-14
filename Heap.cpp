#include "Heap.h"
#include <stdexcept>

heap::heap(std::vector<std::pair<double, int>>& ratioList){
    // build the heap from the ratio list
    for(const auto& node : ratioList) {
        insert(node.first, node.second);
    }
    heapify(0);
    }

void heap::heapifyDown(std::vector<std::pair<double, int>>& heap,int heapSize, int index, int& opCount) {
    while (true) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heapSize) {
            opCount++;
            if (heap[left].first > heap[largest].first) {
                largest = left;
            }
        }

        if (right < heapSize) {
            opCount++;
            if (heap[right].first > heap[largest].first) {
                largest = right;
            }
        }

        if (largest == index) {
            break;
        }

        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}

    heapNode heap::extractMax(){
        if (heapNodes.empty()) {
            throw std::runtime_error("Heap is empty");
        }

        heapNode maxNode = heapNodes[0];
        heapNodes[0] = heapNodes.back();
        heapNodes.pop_back();
        heapifyDown(heapNodes, heapNodes.size(), 0, opCount);

        return maxNode;
        }