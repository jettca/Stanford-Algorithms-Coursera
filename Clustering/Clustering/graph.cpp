//
//  graph.cpp
//  Clustering
//

#include "graph.h"

using namespace std;

graph::graph() :
nodes(vector<node>()),
edges(edge_map()),
edgelist(vector<edge>()),
uf(union_find())
{}

void graph::addEdge(node n1, node n2, edge e)
{
    vector<node> little;
    little.push_back(n1);
    little.push_back(n2);
    
    for(auto n : little)
    {
        int pos = n.num() - 1;
        if(n.num() > nodes.size())
        {
            nodes.resize(n.num());
            nodes[pos] = n;
        }
        else if(nodes[pos].num() == -1)
            nodes[pos] = n;
    }
    
    pair<int, int> toAdd;
    toAdd.first = n1.num();
    toAdd.second = n2.num();
    
    tempedges[e] = toAdd;
    edgelist.push_back(e);
}

void graph::buildUnion()
{
    for(int i = 0; i < nodes.size(); i++)
        uf.add(&nodes[i]);
    
    for(auto iter : tempedges)
        edges[iter.first] = pair<node*, node*>(&nodes[iter.second.first - 1], &nodes[iter.second.second - 1]);
}

void graph::unionize(const edge &e)
{
    uf.unionize(edges[e].first, edges[e].second);
}

const node * graph::find(const node  * n) const
{
    return uf.find(n);
}

int graph::numClusters() const
{
    return uf.numClusters();
}

const union_find graph::unionFind() const
{
    return unionFind();
}

vector<edge> graph::edgeList() const
{
    return edgelist;
}

const node * graph::node1(const edge& e)
{
    return edges[e].first;
}

const node * graph::node2(const edge& e)
{
    return edges[e].second;
}