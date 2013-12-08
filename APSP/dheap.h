//
//  dheap.h
//  APSP
//

#ifndef APSP_dheap_h
#define APSP_dheap_h

#include "graph.h"

typedef unsigned long ulong;
typedef boost::unordered_map<vertex, ulong, vertex_hash> vulong_map;
typedef boost::unordered_map<vertex, float, vertex_hash> vfloat_map;

class dheap
{
public:
    // Construct heap for Dijkstra's algorithm; initially empty
    dheap();
    
    // Insert vertex v with given key
    void insert(const vertex& v, float key);
    
    // Extract vertex with minimum key
    vertex extractMin();
    
    // Remove vertex v
    void remove(const vertex& v);
    
    // Get key for vertex v
    float getkey(const vertex& v) const;
    
    // Number of elements before first meaningless position
    ulong size() const;
    
private:
    // Maintain heap property
    void bubbleUp(ulong curpos);
    void bubbleDown(ulong curpos);
    
    // Helper function for bubbleDown
    ulong validPos(ulong * postoswap, ulong curpos) const;
    
    // Swap two elements in heap
    void swap(ulong pos1, ulong pos2);
    
    // Double size of heap vector
    void increaseSize();
    
    // Get positions of relations
    ulong parent(ulong pos) const;
    ulong leftChild(ulong pos) const;
    ulong rightChild(ulong pos) const;
    
    // Book-keeping
    ulong lastpos;
    ulong heaplength;
    
    // Heap as vector of vertex pointers
    std::vector<vertex> heap;
    
    // Positions of vertices in heap
    vulong_map vertexPos;
    
    // Keys for vertices in heap
    vfloat_map vertexKeys;
};

#endif
