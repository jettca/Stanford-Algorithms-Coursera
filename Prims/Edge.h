//
//  Edge.h
//  Prims
//

#include <boost/unordered_map.hpp>

class Edge
{
public:
    Edge();
    Edge(float weight, int num, int n1, int n2);
    bool operator== (const Edge& edge) const;
    float getWeight() const;
    int getNum() const;
    int getN1() const;
    int getN2() const;
    
private:
    float weight;
    int num, n1, n2;
};

struct Edge_hash : std::unary_function<Edge, size_t>
{
    std::size_t operator()(const Edge& edge) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, edge.getNum());
        return seed;
    }
};