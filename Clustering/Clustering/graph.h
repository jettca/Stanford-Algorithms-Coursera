//
//  graph.h
//  Clustering
//

#ifndef Clustering_graph_h
#define Clustering_graph_h

#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "union_find.h"
#include "edge.h"

typedef boost::unordered_map<edge, std::pair<node*, node*>, edge_hash> edge_map;
typedef boost::unordered_map<edge, std::pair<int, int>, edge_hash> temp_map;

class graph
{
public:
    graph();
    void addEdge(node n1, node n2, edge e);
    void buildUnion();
    void unionize(const edge& e);
    const node * find(const node * n) const;
    int numClusters() const;
    const union_find unionFind() const;
    std::vector<edge> edgeList() const;
    const node * node1(const edge& e);
    const node * node2(const edge& e);
    
private:
    std::vector<node> nodes;
    std::vector<edge> edgelist;
    edge_map edges;
    temp_map tempedges;
    union_find uf;
};

#endif