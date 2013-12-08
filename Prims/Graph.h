//
//  Graph.h
//  Prims
//

#include "Node.h"
#include <boost/unordered_set.hpp>

class Graph
{
public:
    Graph();
    void addNode(Node& node, boost::unordered_set<Edge, Edge_hash> es);
    
    boost::unordered_map<Edge, std::pair<Node*, Node*>, Edge_hash> edges;
    boost::unordered_map<Node*, boost::unordered_set<Edge, Edge_hash>> nodes;
};