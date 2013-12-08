//
//  main.cpp
//  Clustering
//

#include <iostream>
#include <sstream>
#include <fstream>

#include "graph.h"

using namespace std;

void merge(vector<edge>& edges, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    vector<edge> temp;
    while(i <= mid and j <= high)
    {
        if(edges[i] < edges[j])
        {
            temp.push_back(edges[i]);
            i++;
        }
        else
        {
            temp.push_back(edges[j]);
            j++;
        }
    }
    
    for(int k = i; k <= mid; k++)
        temp.push_back(edges[k]);
    for(int k = j; k <= high; k++)
        temp.push_back(edges[k]);

    for(int k = low; k <= high; k++)
        edges[k] = temp[k - low];
}

void mergeSortRecur(vector<edge>& edges, int low, int high)
{
    if(high == low)
        return;
    int mid = (low + high) / 2;
    mergeSortRecur(edges, low, mid);
    mergeSortRecur(edges, mid + 1, high);
    merge(edges, low, mid, high);
}

void mergeSort(vector<edge>& edges)
{
    mergeSortRecur(edges, 0, (int)edges.size() - 1);
}

float maxSpaceKCluster(graph g, unsigned int k)
{
    g.buildUnion();
    
    vector<edge> edges = g.edgeList();
    mergeSort(edges);
        
    int i = 0;
    while(g.numClusters() > k)
    {
        if(g.find(g.node1(edges[i])) != g.find(g.node2(edges[i])))
        {
            edge& e = edges[i];
            g.unionize(e);
        }
        i++;
    }
    
    float maxSpace = 0;
    bool minNotFound = true;
    while(minNotFound)
    {
        if(g.find(g.node1(edges[i])) != g.find(g.node2(edges[i])))
        {
            maxSpace = edges[i].weight();
            minNotFound = false;
        }
        i++;
    }
    
    return maxSpace;
}

int main(int argc, const char * argv[])
{
    graph g;
    
    ifstream infile("clustering1.txt");
    int i = 0;
    string line;
    
    while(infile.good())
    {
        i++;
        getline(infile, line);
        istringstream ss(line);
        string n1, n2, e;
        
        getline(ss, n1, ' ');
        getline(ss, n2, ' ');
        getline(ss, e, ' ');
        
        int num1, num2, weight;
        num1 = atoi(n1.c_str());
        num2 = atoi(n2.c_str());
        weight = atoi(e.c_str());
        
        g.addEdge(node(num1), node(num2), edge(i, weight));
    }
    
    cout << maxSpaceKCluster(g, 4);
    
    return 0;
}