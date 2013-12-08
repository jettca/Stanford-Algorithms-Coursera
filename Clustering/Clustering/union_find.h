//
//  union_find.h
//  Clustering
//

#ifndef Clustering_union_find_h
#define Clustering_union_find_h

#include "node.h"
#include <boost/unordered_map.hpp>

typedef boost::unordered_map<const node*, std::vector<node*>> cluster_map;

class union_find
{
public:
    union_find();
    void add(node * n);
    const node * find(const node * n) const;
    void unionize(const node * n1, const node * n2);
    int numClusters() const;

private:
    cluster_map clusters;
    int numclusters;
};

#endif