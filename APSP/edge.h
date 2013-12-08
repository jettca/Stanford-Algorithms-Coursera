//
//  edge.h
//  APSP
//

#ifndef APSP_edge_h
#define APSP_edge_h

class edge
{
public:
    // default n to 0, weight to infinity, vertices to nullptr
    edge();
    
    edge(long num, float weight);
    
    // getters
    unsigned long num() const;
    float weight() const;
    
    bool operator== (const edge& e) const;
    
private:
    unsigned long n;
    float w;
};

// edges will be hased by num()
struct edge_hash : std::unary_function<edge, size_t>
{
    std::size_t operator() (const edge& e) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, e.num());
        return seed;
    }
};

struct edgeptr_hash : std::unary_function<edge*, size_t>
{
    std::size_t operator() (const edge* const eptr) const
    {
        edge_hash eh;
        return eh(*eptr);
    }
};

#endif