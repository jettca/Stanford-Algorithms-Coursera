//
//  dijkstras.h
//  APSP
//

#ifndef APSP_dijkstras_h
#define APSP_dijkstras_h

#include "dheap.h"

typedef boost::unordered_set<vertex, vertex_hash> vertex_set;

// Run Dijkstra's algorithm on graph g from source
vfloat_map dijkstras(const graph& g, const vertex& source);

// Update the heap of vertices after extracting the minimum
void updateHeap(const graph& g, const vertex& removed, const vertex_set& explored, dheap& heap);

#endif