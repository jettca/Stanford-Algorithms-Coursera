//
//  johnsons.cpp
//  APSP
//

#include "johnsons.h"

using namespace std;

vtovf_map johnsons(const graph& g)
{
    vtovf_map results;
    
    // Get old graph data
    edge_vector emap = g.getEdgeMap();
    ev edges = g.getEdges();
    vv vertices = g.getVertices();
    vv tails, heads;
    
    ulong numedges = edges.size();
    for(int i = 0; i < numedges; i++)
    {
        tails.push_back(*emap[i].first);
        heads.push_back(*emap[i].second);
    }
    
    pair<graph, vertex> ghostG(gPrime(edges, tails, heads, vertices));
    
    vtof_map shifts(BellmanFord(ghostG.first, ghostG.second));
    
    graph newg(reweight(edges, tails, heads, shifts));
    
    ev newedges(newg.getEdges());
    
    // Run Dijkstra's on every vertex in newg
    for(const_v_iter iter = newg.vbegin(); iter != newg.vend(); iter++)
        results[*iter] = dijkstras(newg, *iter);
    
    // Correct weights
    for(vtovf_map::iterator iter1 = results.begin(); iter1 != results.end(); iter1++)
    {
        for(vfloat_map::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++)
        {
            vertex s = iter1->first;
            vertex d = iter2->first;
            results[s][d] = results[s][d] - shifts[s] + shifts[d];
        }
    }
    
    return results;
}

pair<graph, vertex> gPrime(ev edges, vv tails, vv heads, const vv& vertices)
{
    // Add ghost vertex
    ulong numv = vertices.size();
    ulong numedges = edges.size();
    vertex ghost(numv + 1);
    
    for(int i = 0; i < numv; i++)
    {
        edges.push_back(edge(numedges + i + 1, 0));
        tails.push_back(ghost);
        heads.push_back(vertices[i]);
    }
    
    return pair<graph, vertex>(graph(edges, tails, heads), ghost);
}

graph reweight(ev edges, const vv& tails, const vv& heads, const vtof_map& shifts)
{
    ev newedges;
    
    ulong numedges = edges.size();
    for(int i = 0; i < numedges; i++)
    {
        float newweight = edges[i].weight() + shifts.at(tails.at(i)) - shifts.at(heads.at(i));
        newedges.push_back(edge(i + 1, newweight));
    }
    
    return graph(newedges, tails, heads);
}