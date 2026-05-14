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

        void heapify(int index){
            for (size_t i = 0; i < heapNodes.size(); i++)
            {
                heapifyDown(heapNodes, heapNodes.size(), i, opCount);
            }
            
        }

        int getOpCount() const {
            return opCount;
        }

        heapNode extractMax();

    private:
        std::vector<heapNode> heapNodes;
        int opCount = 0;
};