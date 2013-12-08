//
//  dheap.cpp
//  APSP
//

#include "dheap.h"

using namespace std;

dheap::dheap() :
lastpos(0),
heaplength(1),
heap(vector<vertex>()),
vertexPos(vulong_map()),
vertexKeys(vfloat_map())
{
    heap.resize(1);
}

void dheap::insert(const vertex& v, float key)
{
    // Insert v
    lastpos++;
    heap[lastpos - 1] = v;
    vertexPos[v] = lastpos;
    
    // Set key
    vertexKeys[v] = key;
    
    if(lastpos >= heaplength)
        increaseSize();
    
    // Correct heap
    bubbleUp(lastpos);
}

vertex dheap::extractMin()
{
    // Artificially remove minimum vertex
    vertex minv = heap[0];
    swap(1, lastpos);
    lastpos--;
    
    // Correct heap
    bubbleDown(1);
    
    // Remove from pos
    vertexPos.erase(minv);
    
    return minv;
}

void dheap::remove(const vertex& v)
{
    // Do nothing if node not in heap
    if(vertexPos.find(v) != vertexPos.end())
    {
        // Artificially remove v
        ulong removepos = vertexPos[v];
        swap(removepos, lastpos);
        lastpos--;
        
        // Correct heap
        bubbleUp(removepos);
        bubbleDown(removepos);
        
        // Remove from map
        vertexPos.erase(v);
    }
}

float dheap::getkey(const vertex &v) const
{
    return vertexKeys.at(v);
}

ulong dheap::size() const
{
    return lastpos;
}

void dheap::bubbleUp(ulong curpos)
{
    vertex v = heap[curpos - 1];
    ulong parentpos = parent(curpos);
    
    // Bubble up until v is smaller than its parent
    while(parentpos > 0 and vertexKeys[v] < vertexKeys[heap[parentpos - 1]])
    {
        swap(curpos, parentpos);
        curpos = parentpos;
        parentpos = parent(curpos);
    }
}

void dheap::bubbleDown(ulong curpos)
{
    // Array containing children of curpos that fail heap property
    ulong * postoswap = new ulong[2];
    
    // arrsize is number of children of curpos failing heap property
    // postoswap updated as side effect
    short arrsize = validPos(postoswap, curpos);
    
    while(arrsize > 0)
    {
        // swap with minimum of bad children
        ulong minpos = postoswap[0];

        if(arrsize == 2 and vertexKeys[heap[postoswap[1] - 1]] < vertexKeys[heap[minpos - 1]])
        {
            minpos = postoswap[1];
        }
        
        swap(curpos, minpos);
        curpos = minpos;
        arrsize = validPos(postoswap, curpos);
    }
    
    delete postoswap;
}

ulong dheap::validPos(ulong * postoswap, ulong curpos) const
{
    ulong lchild = leftChild(curpos);
    ulong rchild = rightChild(curpos);
    int arrsize = 0;
    
    // If lchild/rchild fails heap property, add to postoswap
    if(lchild <= lastpos and vertexKeys.at(heap.at(lchild - 1)) < vertexKeys.at(heap.at(curpos - 1)))
    {
        postoswap[0] = lchild;
        arrsize++;
    }
    
    if(rchild <= lastpos and vertexKeys.at(heap.at(rchild - 1)) < vertexKeys.at(heap.at(curpos - 1)))
    {
        postoswap[arrsize] = rchild;
        arrsize++;
    }
    
    return arrsize;
}

void dheap::swap(ulong pos1, ulong pos2)
{
    // Swap position mappings
    vertexPos[heap[pos1 - 1]] = pos2;
    vertexPos[heap[pos2 - 1]] = pos1;
    
    // Swap heap positions
    vertex temp = heap[pos1 - 1];
    heap[pos1 - 1] = heap[pos2 - 1];
    heap[pos2 - 1] = temp;
}

void dheap::increaseSize()
{
    heap.resize(heaplength * 2);
    heaplength *= 2;
}

ulong dheap::parent(ulong pos) const
{
    return pos / 2;
}

ulong dheap::leftChild(ulong pos) const
{
    return pos * 2;
}

ulong dheap::rightChild(ulong pos) const
{
    return pos * 2 + 1;
}