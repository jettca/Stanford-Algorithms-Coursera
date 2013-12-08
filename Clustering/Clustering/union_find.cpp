//
//  union_find.cpp
//  Clustering
//

#include "union_find.h"

using namespace std;

union_find::union_find() :
clusters(cluster_map()),
numclusters(0)
{}

void union_find::add(node * n)
{
    n->setLeader(n);
    if(clusters.find(n) == clusters.end())
    {        
        vector<node*> nodes;
        nodes.push_back(n);
        
        clusters[n] = nodes;
        numclusters++;
    }
    else
        clusters[n].push_back(n);
}

const node * union_find::find(const node * n) const
{
    return n->leader();
}

void union_find::unionize(const node * n1, const node * n2)
{
    const node * move, * target;
    if(clusters.at(n1->leader()).size() > clusters.at(n2->leader()).size())
    {
        move = n2->leader();
        target = n1->leader();
    }
    else
    {
        move = n1->leader();
        target = n2->leader();
    }

    const vector<node*>& toMove = clusters[move];
    for(auto node : toMove)
    {
        node->setLeader(target);
        clusters[target].push_back(node);
    }
    
    clusters.erase(move);
    
    numclusters--;
}

int union_find::numClusters() const
{
    return numclusters;
}
