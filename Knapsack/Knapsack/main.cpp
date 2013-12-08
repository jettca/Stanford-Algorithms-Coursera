//
//  main.cpp
//  Knapsack
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/unordered_map.hpp>
#include "item.h"

using namespace std;

typedef boost::unordered_map<pair<int, int>, int> int_pair_to_int;

int max(int val1, int val2)
{
    if(val1 > val2)
        return val1;
    
    return val2;
}

int knapsackVal(vector<item> items, int weight)
{
    int size = (int)items.size();
    vector<vector<int>> values(size, vector<int>(weight + 1));
    values[0][0] = 0;
    
    for(int w = 0; w <= weight; w++)
    {
        values[0][w] = 0;
        for(int i = 1; i < size; i++)
        {
            int hasItemVal = -1;
            if(w >= items[i].weight)
                hasItemVal = values[i - 1][w - items[i].weight] + items[i].value;
            
            values[i][w] = max(values[i - 1][w], hasItemVal);
        }
    }
    
    return values[size - 1][weight];
}

int knapsackValRecur(const vector<item>& items, int_pair_to_int& ixToV, int i, int x)
{
    pair<int, int> ix(i, x);
    int maxVal;
    
    if(ixToV.find(ix) != ixToV.end())
        return ixToV[ix];
    
    if(x < 0)
    {
        maxVal = -items[i + 1].value;
    }
    else if(i == 0)
    {
        maxVal = 0;
    }
    else
    {
        maxVal = max(knapsackValRecur(items, ixToV, i - 1, x),
                     knapsackValRecur(items, ixToV, i - 1, x - items[i].weight) + items[i].value);
    }
    
    ixToV[ix] = maxVal;
    return maxVal;
}

int knapsackVal2(const vector<item>& items, int weight)
{
    int_pair_to_int ixToV;
    return knapsackValRecur(items, ixToV, (int)items.size(), weight);
}

int main(int argc, const char * argv[])
{
    ifstream infile;
    infile.open("knapsack2.txt");
    
    string line1;
    getline(infile, line1);
    istringstream ss(line1);
    
    string size, numitems;
    getline(ss, size, ' ');
    getline(ss, numitems, ' ');
    
    vector<item> items;
    
    while(infile.good())
    {
        string line;
        getline(infile, line);
        istringstream ss(line);
        
        string val_s, weight_s;
        getline(ss, val_s, ' ');
        getline(ss, weight_s, ' ');
        
        int val = atoi(val_s.c_str());
        int weight = atoi(weight_s.c_str());
        
        items.push_back(item(val, weight));
    }
    
    cout << knapsackVal2(items, atoi(size.c_str()));
    
    return 0;
}