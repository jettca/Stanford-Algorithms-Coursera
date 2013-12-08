//
//  Graph.cpp
//  Prims
//

#include "Graph.h"

using namespace std;

Graph::Graph() :
edges(boost::unordered_map<Edge, pair<Node*, Node*>, Edge_hash>()),
nodes(boost::unordered_map<Node*, boost::unordered_set<Edge, Edge_hash>>())
{}

void Graph::addNode(Node& node, boost::unordered_set<Edge, Edge_hash> es)
{
    nodes[&node] = es;

    for(auto iter : es)
    {
        if(edges.find(iter) == edges.end())
            edges[iter] = pair<Node*, Node*>(&node, nullptr);
        if(edges.count(iter) > 0 or iter.getN1() == iter.getN2())
            edges[iter].second = &node;
    }
}