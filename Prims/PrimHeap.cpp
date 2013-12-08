//
//  PrimHeap.cpp
//  Prims
//

#include "PrimHeap.h"
#include <iostream>

using namespace std;

PrimHeap::PrimHeap() :
lastPos(0),
heapLength(1),
heap(vector<Node*>()),
nodePos(boost::unordered_map<Node, int, Node_hash>())
{
    heap.resize(1);
}

void PrimHeap::insert(Node& node)
{
    lastPos++;
    heap[lastPos - 1] = &node;
    nodePos[node] = lastPos;
    
    if(lastPos >= heapLength)
        increaseSize();
    
    bubbleUp(lastPos);
}

Node& PrimHeap::extractMin()
{
    Node& nodeToReturn = *heap[0];
    swap(1, lastPos);
    lastPos--;
    
    bubbleDown(1);
    
    return nodeToReturn;
}

void PrimHeap::remove(const Node& node)
{
    // Return if node not in heap
    if(nodePos.find(node) == nodePos.end())
        return;
    int removePos = nodePos[node];
    swap(removePos, lastPos);
    lastPos--;
    
    bubbleUp(removePos);
    bubbleDown(removePos);
}

int PrimHeap::size()
{
    return lastPos;
}

void PrimHeap::print()
{
    cout << "Size: " << heapLength << " " << lastPos << "\n";
    for(int i = 1; i <= lastPos; i++)
        heap[i - 1]->print();
}

void PrimHeap::bubbleUp(int curPos)
{
    Node node = *heap[curPos - 1];
    int parentPos = parent(curPos);
    while(parentPos > 0 and node < *heap[parentPos - 1])
    {
        swap(curPos, parentPos);
        curPos = parentPos;
        parentPos = parent(curPos);
    }
}

void PrimHeap::bubbleDown(int curPos)
{
    // Array containing child nodes failing heap property
    int * goodPos = new int[2];
    
    // arrSize is number of bad children of curPos; goodPos updated as side effect
    int arrSize = validPos(goodPos, curPos);
    
    while(arrSize > 0)
    {
        // Swap with minimum of bad children
        int minPos = goodPos[0];
        if(arrSize == 2 and *heap[goodPos[1] - 1] < *heap[minPos - 1])
            minPos = goodPos[1];
        
        swap(curPos, minPos);
        curPos = minPos;
        arrSize = validPos(goodPos, curPos);
    }
    delete goodPos;
}

int PrimHeap::validPos(int * goodPos, int curPos)
{
    int lChild = leftChild(curPos);
    int rChild = rightChild(curPos);
    int arrSize = 0;
    
    if(lChild <= lastPos and *heap[lChild - 1] < *heap[curPos - 1])
    {
        goodPos[0] = lChild;
        arrSize++;
    }
    if(rChild <= lastPos and *heap[rChild - 1] < *heap[curPos - 1])
    {
        // Puts right child position at 0 if only bad child, 1 if second bad child
        goodPos[arrSize] = rChild;
        arrSize++;
    }
    return arrSize;
}

void PrimHeap::swap(int pos1, int pos2)
{
    nodePos[*heap[pos1 - 1]] = pos2;
    nodePos[*heap[pos2 - 1]] = pos1;
    
    Node * temp = heap[pos1 - 1];
    heap[pos1 - 1] = heap[pos2 - 1];
    heap[pos2 - 1] = temp;
}

void PrimHeap::increaseSize()
{
    heap.resize(heapLength*2);
    heapLength *= 2;
}

int PrimHeap::parent(int pos)
{
    return pos / 2;
}

int PrimHeap::leftChild(int pos)
{
    return pos * 2;
}

int PrimHeap::rightChild(int pos)
{
    return pos * 2 + 1;
}