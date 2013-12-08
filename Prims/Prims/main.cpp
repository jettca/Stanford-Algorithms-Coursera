//
//  main.cpp
//  Prims
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/unordered_set.hpp>

#include "PrimHeap.h"

using namespace std;

typedef boost::unordered_set<Edge, Edge_hash> edge_set;
typedef boost::unordered_set<Node, Node_hash> node_set;

// Update key values in pheap after n is extracted from pheap and added to explored
void updateHeap(Graph& g, Node& n, PrimHeap& pheap, node_set& explored)
{
    for(auto edge : g.nodes[&n])
    {
        // Set w to adjacent node along edge
        Node * w;
        if(*g.edges[edge].first == n)
            w = g.edges[edge].second;
        else
            w = g.edges[edge].first;
        
        // Update minimum edge if w is unexplored
        if(explored.find(*w) == explored.end())
            if(edge.getWeight() < w->getKey())
            {
                pheap.remove(*w);
                w->setMinEdge(edge);
                pheap.insert(*w);
            }
    }
}

edge_set PrimsMST(Graph& g, const Node& source)
{
    PrimHeap pheap;
    
    edge_set mst;
    node_set explored;
        
    // Load nodes into heap
    typedef boost::unordered_map<Node*, edge_set> node_map;
    for(node_map::iterator iter = g.nodes.begin(); iter != g.nodes.end(); iter++)
    {
        Node * n = iter->first;
        pheap.insert(*n);
    }
    explored.insert(source);
    pheap.remove(source);
    
    unsigned long numNodes = g.nodes.size();
    while(explored.size() < numNodes)
    {
        // Add minimum edge on frontier to explored
        Node& n = pheap.extractMin();
        explored.insert(n);
        mst.insert(n.getEdge());
        updateHeap(g, n, pheap, explored);
    }
    return mst;
}

void insertAt(vector<Node>& nodes, vector<edge_set>& edges, int node1, int node2, int weight, int i)
{
    if(node1 <= nodes.size())
    {
        if(nodes[node1 - 1].getNum() == -1)
        {
            nodes[node1 - 1] = Node(node1);
            boost::unordered_set<Edge, Edge_hash> es;
            es.insert(Edge(weight, i, node1, node2));
            edges[node1 - 1] = es;
        }
        else
            edges[node1 - 1].insert(Edge(weight, i, node1, node2));
    }
    else
    {
        nodes.resize(node1);
        edges.resize(node1);
        nodes.insert(nodes.begin() + node1 - 1, Node(node1));
        boost::unordered_set<Edge, Edge_hash> es;
        es.insert(Edge(weight, i, node1, node2));
        edges.insert(edges.begin() + node1 - 1, es);
    }
}

int main(int argc, const char * argv[])
{
    ifstream infile("edges.txt");
    
    Graph g;
    int i = 0;
    string line;
    getline(infile, line);
    vector<Node> nodes;
    vector<edge_set> edges;
    
    while(infile.good())
    {
        i++;
        getline(infile, line);
        istringstream ss(line);
        
        string n1, n2, e;
        getline(ss, n1, ' ');
        getline(ss, n2, ' ');
        getline(ss, e, ' ');
        
        int node1, node2, weight;
        node1 = atoi(n1.c_str());
        node2 = atoi(n2.c_str());
        weight = atoi(e.c_str());
        
        insertAt(nodes, edges, node1, node2, weight, i);
        insertAt(nodes, edges, node2, node1, weight, i);
    }
    Node& source = nodes[0];
    int size = (int)nodes.size();
    for(int i = 0; i < size; i++)
    {
        Edge minEdge;
        for(auto iter : edges[i])
        {
            if(iter.getWeight() < minEdge.getWeight())
            {
                if(iter.getN1() == source.getNum() or iter.getN2() == source.getNum())
                    minEdge = iter;
            }
        }
        nodes[i].setMinEdge(minEdge);
        g.addNode(nodes[i], edges[i]);
    }
    
    edge_set mst = PrimsMST(g, source);
    long cost = 0;
    for(auto edge: mst)
        cost += edge.getWeight();
    
    cout << cost;
    
    return 0;
}