//
//  johnsons.h
//  APSP
//

#include "BellmanFord.h"
#include "dijkstras.h"

#ifndef APSP_johnsons_h
#define APSP_johnsons_h

typedef boost::unordered::unordered_map<vertex, vfloat_map, vertex_hash> vtovf_map;

typedef std::vector<edge> ev;
typedef std::vector<vertex> vv;

// Returns all-pairs shortest paths for g
vtovf_map johnsons(const graph& g);

// Returns g and added ghost vertex
std::pair<graph, vertex> gPrime(ev edges, vv tails, vv heads, const vv& vertices);

// Returns a reweighted graph for Johnson's algorithm
graph reweight(ev edges, const vv& tails, const vv& heads, const vtof_map& shifts);

#endif
