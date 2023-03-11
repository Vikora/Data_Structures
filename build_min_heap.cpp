#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

// Convert an array of integers into a heap
class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;
    
    int getParent(int node) {
        return (node-1) / 2;    
    }

    int getLeftChild(int node) {
        return 2*node + 1;
    }
    
    int getRightChild(int node) {
        return 2*node + 2;
    }

    void siftDown(int node) {
        size_t leftChild, rightChild;
        int minIndex = node;
        do {
            node = minIndex;
            leftChild = getLeftChild(node);
            rightChild = getRightChild(node);

            if (leftChild < data_.size() && data_[leftChild] < data_[minIndex])
                minIndex = leftChild;
            if (rightChild < data_.size() && data_[rightChild] < data_[minIndex])
                minIndex = rightChild;

            if (node != minIndex) {
                swap(data_[node], data_[minIndex]);
                // record a swap
                swaps_.push_back(make_pair(node, minIndex));
            }
        } while (minIndex != node);
    }

    void GenerateSwaps() {
        /*
         Ascending sort.
         Treating data_ as a binary min-heap (binary tree)
         Root is the minimum element
        */
        /* Build Heap:
            siftdown all nodes except the lowest level */
        for (int i = data_.size() / 2; i >= 0; --i)
            siftDown(i);
    }

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (size_t i = 0; i < swaps_.size(); ++i) {
            printf("%d %d\n", swaps_[i].first, swaps_[i].second);
        }
        /*for (int i = 0; i < data_.size(); ++i) {
            cout << data_[i] << " ";
        }
        cout << "\n";*/

    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

public:
    void Solve() {
        // read from input
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    HeapBuilder heapBuilder;
    heapBuilder.Solve();
    return 0;
}
