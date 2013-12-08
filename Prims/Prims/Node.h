//
//  Node.h
//  Prims
//

#include <boost/unordered_map.hpp>
#include "Edge.h"

class Node
{
public:
    Node();
    Node(int num);
    Node(int num, Edge e);
    int getNum() const;
    float getKey() const;
    Edge getEdge() const;
    void setMinEdge(Edge edge);
    bool operator== (const Node& node) const;
    bool operator< (const Node& node) const;
    
    void print() const;
    
private:
    int num;
    Edge minEdge;
};

struct Node_hash : std::unary_function<Node, size_t>
{
    std::size_t operator()(const Node& node) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, node.getNum());
        return seed;
    }
};