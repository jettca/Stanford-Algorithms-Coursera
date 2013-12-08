//
//  vertex.h
//  APSP
//

#ifndef APSP_vertex_h
#define APSP_vertex_h

#include <boost/unordered_set.hpp>

class vertex
{
public:
    // default n to 0
    vertex();
    
    vertex(long num);
    
    unsigned long num() const;
    
    bool operator== (const vertex& v) const;
    
private:
    // vertex identifier
    unsigned long n;
};

// vertices will be hashed by num()
struct vertex_hash : std::unary_function<vertex, size_t>
{
    std::size_t operator() (const vertex& v) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.num());
        return seed;
    }
};

struct vertexptr_hash : std::unary_function<vertex*, size_t>
{
    std::size_t operator() (const vertex* const vptr) const
    {
        vertex_hash vh;
        return vh(*vptr);
    }
};

#endif
