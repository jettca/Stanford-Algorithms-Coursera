//
//  PrimHeap.h
//  Prims
//

#include "Graph.h"
#include <boost/unordered_map.hpp>
#include <vector>

class PrimHeap
{
public:
    PrimHeap();
    
    void insert(Node& node);
    
    Node& extractMin();
    
    void remove(const Node& node);
    
    int size();
    
    void print();
    
private:
    void bubbleUp(int curPos);
    void bubbleDown(int curPos);
    int validPos(int * goodPos, int curPos);
    void swap(int pos1, int pos2);
    void increaseSize();
    int parent(int pos);
    int leftChild(int pos);
    int rightChild(int pos);
    
    int lastPos;
    int heapLength;

    std::vector<Node *> heap;
    boost::unordered_map<Node, int, Node_hash> nodePos;
};