//
//  edge.h
//  Clustering
//

#ifndef Clustering_edge_h
#define Clustering_edge_h

#include <boost/unordered_map.hpp>

class edge
{
public:
    edge(unsigned int num, float weight);
    int num() const;
    float weight() const;
    
    bool operator== (const edge& e) const;
    bool operator< (const edge& e) const;
    bool operator> (const edge& e) const;

private:
    int n;
    float w;
};

struct edge_hash : std::unary_function<edge, std::size_t>
{
    std::size_t operator()(const edge& e) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, e.num());
        return seed;
    }
};

#endif