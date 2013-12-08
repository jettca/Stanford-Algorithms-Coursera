//
//  node.h
//  Clustering
//

#ifndef Clustering_node_h
#define Clustering_node_h

#include <boost/unordered_map.hpp>

class node
{
public:
    node();
    node(unsigned int num);
    void setLeader(const node * nptr);
    bool operator== (const node& n) const;
    int num() const;
    const node * leader() const;

private:
    int n;
    const node * leadptr;
};

#endif