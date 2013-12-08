//
//  dijkstras.cpp
//  APSP
//

#include "dijkstras.h"

using namespace std;

vfloat_map dijkstras(const graph& g, const vertex& source)
{
    vfloat_map results;
    
    dheap heap;
    vertex_set explored;
    
    // Load vertices into heap
    for(const_v_iter iter = g.vbegin(); iter != g.vend(); ++iter)
    {
        float key = std::numeric_limits<float>::infinity();
        vertex v = *iter;
        
        // Set initial key value
        const edgeptr_set * eintov = g.edgesInto(v);
        for(auto iter : *eintov)
            if(g.tail(*iter)->num() == source.num())
                key = iter->weight();
               
        heap.insert(v, key);
    }
    
    heap.remove(source);
    explored.insert(source);
    
    ulong numv = g.numVertices();
    while(explored.size() < numv)
    {
        // Add vertex to explored and update heap
        const vertex& v = heap.extractMin();
        results[v] = heap.getkey(v);
        explored.insert(v);
        updateHeap(g, v, explored, heap);
    }
    
    return results;
}

void updateHeap(const graph& g, const vertex& removed, const vertex_set& explored, dheap& heap)
{
    const edgeptr_set * eintor = g.edgesInto(removed);
    
    for(auto edge : *eintor)
    {
        vertex w = *g.tail(*edge);
        
        // Update key for w if w is unexplored
        if(explored.find(w) == explored.end())
        {
            float costWithEdge = heap.getkey(removed) + edge->weight();
            if(heap.getkey(w) > costWithEdge)
            {
                heap.remove(w);
                heap.insert(w, costWithEdge);
            }
        }
    }
}