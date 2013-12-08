//
//  edge.cpp
//  APSP
//

#include "edge.h"
#include <iostream>

edge::edge() :
n(0),
w(std::numeric_limits<double>::infinity())
{}

edge::edge(long num, float weight) :
n(num),
w(weight)
{
    if(num <= 0)
    {
        std::cout << "Warning: Num must be greater than 0.  Setting to 0.\n";
        n = 0;
    }
}

unsigned long edge::num() const
{
    return n;
}

float edge::weight() const
{
    return w;
}

bool edge::operator== (const edge& e) const
{
    return n == e.num();
}