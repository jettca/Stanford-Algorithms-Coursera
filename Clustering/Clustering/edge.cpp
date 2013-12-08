//
//  edge.cpp
//  Clustering
//

#include "edge.h"

edge::edge(unsigned int num, float weight) :
n(num),
w(weight)
{}

int edge::num() const
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

bool edge::operator< (const edge& e) const
{
    return w < e.weight();
}

bool edge::operator> (const edge& e) const
{
    return w > e.weight();
}