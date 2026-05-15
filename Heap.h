#include <vector>
#include <utility>

using heapNode = std::pair<double, int>;

class heap{
    public:
        heap(std::vector<std::pair<double, int>>& ratioList);
        
        void heapifyDown(std::vector<std::pair<double, int>>& heap,int heapSize, int index, int& opCount);

        void insert(double ratio, int index){
            heapNodes.emplace_back(ratio, index);
        }

    void heapify() {
        for (int i = static_cast<int>(heapNodes.size()) / 2 - 1; i >= 0; --i) {
            heapifyDown(heapNodes, static_cast<int>(heapNodes.size()), i, opCount);
        }
    }

        int getOpCount() const {
            return opCount;
        }

        heapNode extractMax();

        void printHeap();

    private:
        std::vector<heapNode> heapNodes;
        int opCount = 0;
};