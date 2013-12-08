//
//  graph.cpp
//  APSP
//

#include "graph.h"
#include <iostream>

using namespace std;

graph::graph(const vector<edge>& uedges, const vector<vertex>& tails, const vector<vertex>& heads) :
edges(vector<edge>()),
vertices(vector<vertex>()),
vinmap(vertex_vector()),
voutmap(vertex_vector()),
emap(edge_vector())
{
    unsigned long numedges = uedges.size();
    
    for(int i = 0; i < numedges; i++)
    {
        // Resize vectors if pos out of range
        unsigned long epos = uedges[i].num() - 1;
        unsigned long tpos = tails[i].num() - 1;
        unsigned long hpos = heads[i].num() - 1;
        
        if((long)epos < 0 or (long)tpos < 0 or (long)hpos < 0)
        {
            cout << "Warning: objects with num 0 inserted.  Ignoring edge.\n";
        }
        else
        {
            if(epos >= emap.size())
            {
                edges.resize(epos + 1);
                emap.resize(epos + 1);
            }
            
            unsigned long mpos = max(tpos, hpos);
            if(mpos >= vertices.size())
            {
                vertices.resize(mpos + 1);
                vinmap.resize(mpos + 1);
                voutmap.resize(mpos + 1);
            }
            
            // Add values to vectors
            edges[epos] = uedges[i];
            vertices[tpos] = tails[i];
            vertices[hpos] = heads[i];
        }
    }
    
    // Add references to maps
    for(int i = 0; i < numedges; i++)
    {
        unsigned long epos = uedges[i].num() - 1;
        unsigned long tpos = tails[i].num() - 1;
        unsigned long hpos = heads[i].num() - 1;
        
        emap[epos] = vertexptr_pair(&vertices[tpos], &vertices[hpos]);
        voutmap[tpos].insert(&edges[epos]);
        vinmap[hpos].insert(&edges[epos]);
    }
}

const edgeptr_set * graph::edgesInto(const vertex& v) const
{
    if(v.num() == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning empty set.\n";
        return nullptr;
    }
    
    return &vinmap[v.num() - 1];
}

edgeptr_set graph::edgesOutof(const vertex& v) const
{
    if(v.num() == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning empty set.\n";
        return edgeptr_set();
    }
    
    return voutmap[v.num() - 1];
}

const vertex * graph::head(const edge& e) const
{
    if(e.num() == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning null.\n";
        return nullptr;
    }
    
    return emap[e.num() - 1].second;
}

const vertex * graph::tail(const edge& e) const
{
    if(e.num() == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning null.\n";
        return nullptr;
    }
    
    return emap[e.num() - 1].first;
}

edgeptr_set graph::edgesInto(unsigned long num) const
{
    if(num == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning empty set.\n";
        return edgeptr_set();
    }
    
    return vinmap[num - 1];
}

edgeptr_set graph::edgesOutof(unsigned long num) const
{
    if(num == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning empty set.\n";
        return edgeptr_set();
    }
    
    return voutmap[num - 1];
}

const vertex * graph::head(unsigned long num) const
{
    if(num == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning null.\n";
        return nullptr;
    }
    
    return emap[num - 1].second;
}

const vertex * graph::tail(unsigned long num) const
{
    if(num == 0)
    {
        cout << "Warning: Num must be greater than 0.  Returning null.\n";
        return nullptr;
    }
    
    return emap[num - 1].first;
}

unsigned long graph::numEdges() const
{
    return edges.size();
}

unsigned long graph::numVertices() const
{
    return vertices.size();
}

edge_vector graph::getEdgeMap() const
{
    return emap;
}

vector<edge> graph::getEdges() const
{
    return edges;
}

vector<vertex> graph::getVertices() const
{
    return vertices;
}