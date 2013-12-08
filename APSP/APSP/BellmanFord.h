//
//  BellmanFord.h
//  APSP
//

#ifndef APSP_BellmanFord_h
#define APSP_BellmanFord_h

#include "graph.h"

typedef boost::unordered_map<vertex, float, vertex_hash> vtof_map;

// Runs the Bellman-Ford algorithm on graph g with given source; returns distances
vtof_map BellmanFord(const graph& g, const vertex& source);

#endif
