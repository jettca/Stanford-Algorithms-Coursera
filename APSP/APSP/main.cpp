//
//  main.cpp
//  APSP
//

#include <iostream>
#include <fstream>
#include <sstream>

#include "johnsons.h"

using namespace std;

int main(int argc, const char * argv[])
{
    // Data to be made into graph
    vector<edge> edges;
    vector<vertex> tails;
    vector<vertex> heads;
    
    // Placeholders for reading in data
    ifstream infile("g3.txt");
    string line, v1_s, v2_s, weight_s;
    unsigned long v1, v2;
    float weight;
    
    // Counter for edge num
    unsigned long i = 1;
    
    while(infile.good())
    {
        getline(infile, line);
        
        istringstream iss(line);
        
        getline(iss, v1_s, ' ');
        getline(iss, v2_s, ' ');
        getline(iss, weight_s, ' ');
        
        // Convert placeholder strings to ints
        v1 = atol(v1_s.c_str());
        v2 = atol(v2_s.c_str());
        weight = atof(weight_s.c_str());
        
        tails.push_back(vertex(v1));
        heads.push_back(vertex(v2));
        edges.push_back(edge(i, weight));
        
        i++;
    }
    
    graph g(edges, tails, heads);
    
    vtovf_map results = johnsons(g);
    
    float minshortest = numeric_limits<float>::infinity();
    
    for(auto iter : results)
    {
        for(auto iter2 : iter.second)
        {
            if(iter2.second < minshortest)
            {
                minshortest = iter2.second;
            }
        }
    }
    
    cout << minshortest;
    
    return 0;
}