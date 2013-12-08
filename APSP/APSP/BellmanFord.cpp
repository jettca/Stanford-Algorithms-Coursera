//
//  BellmanFord.cpp
//  APSP
//

#include "BellmanFord.h"
#import <iostream>

using namespace std;

vtof_map BellmanFord(const graph& g, const vertex& source)
{
    vtof_map results;
    
    unsigned long numv = g.numVertices();
    vector<vector<float>> distances(numv + 1, vector<float>(numv + 1));
    
    // Initialize distances
    distances[0][source.num()] = 0;
    for(int i = 1; i <= numv; i++)
        if(i != source.num())
            distances[0][i] = std::numeric_limits<float>::infinity();
    
    for(int i = 1; i <= numv; i++)
    {
        for(int j = 1; j <= numv; j++)
        {
            // Find best edge into j
            float bestedgedist = std::numeric_limits<float>::infinity();
            
            const edgeptr_set * edgesintoj = g.edgesInto(vertex(j));
            
            for(auto iter : *edgesintoj)
            {
                float edgedist = distances[i-1][g.tail(*iter)->num()] + iter->weight();
                
                if(edgedist < bestedgedist)
                {
                    bestedgedist = edgedist;
                }
            }
            
            distances[i][j] = min(distances[i-1][j], bestedgedist);
        }
    }
    
    for(int i = 1; i <= numv; i++)
    {
        if(distances[numv - 1][i] != distances[numv][i])
        {
            cout << "Has negative cost cycle\n";
            break;
        }
        
        results[vertex(i)] = distances[numv][i];
    }
    
    return results;
}