//
//  graph.h
//  APSP
//

#ifndef APSP_graph_h
#define APSP_graph_h

#include <vector>
#include <boost/unordered_set.hpp>

#include "vertex.h"
#include "edge.h"

typedef boost::unordered_set<const edge*, edgeptr_hash> edgeptr_set;
typedef std::pair<const vertex*, const vertex*> vertexptr_pair;

typedef std::vector<vertexptr_pair> edge_vector;
typedef std::vector<edgeptr_set> vertex_vector;

typedef std::vector<vertex>::const_iterator const_v_iter;
typedef std::vector<edge>::const_iterator const_e_iter;

class graph
{
public:
    // Positions in vectors are correspondance between an edge and its vectors
    graph(const std::vector<edge>& uedges, const std::vector<vertex>& tails, const std::vector<vertex>& heads);
    
    // Get map values
    const edgeptr_set * edgesInto(const vertex& v) const;
    edgeptr_set edgesOutof(const vertex& v)  const;
    const vertex * head(const edge& e) const;
    const vertex * tail(const edge& e) const;
    
    // Get map values with num input
    edgeptr_set edgesInto(unsigned long num) const;
    edgeptr_set edgesOutof(unsigned long num) const;
    const vertex * head(unsigned long num) const;
    const vertex * tail(unsigned long num) const;
    
    // Get sizes
    unsigned long numEdges() const;
    unsigned long numVertices() const;
    
    // Iterators
    const_v_iter vbegin() const { return vertices.begin(); }
    const_v_iter vend() const { return vertices.end(); }
    
    const_e_iter ebegin() const { return edges.begin(); }
    const_e_iter eend() const { return edges.end(); }
    
    // Return copy of graph data
    edge_vector getEdgeMap() const;
    std::vector<edge> getEdges() const;
    std::vector<vertex> getVertices() const;
    
private:
        
    // Vertex and edge storage
    std::vector<vertex> vertices;
    std::vector<edge> edges;
    
    // Map from vertex number to edges of which they are the tail/head
    vertex_vector vinmap;
    vertex_vector voutmap;
    
    // Map from edge number to (tail, head) pair
    edge_vector emap;
};

#endif