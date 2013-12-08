//
//  Edge.cpp
//  Prims
//

#include "Edge.h"

Edge::Edge() :
weight(std::numeric_limits<double>::infinity()),
num(-1),
n1(-1),
n2(-1)
{}

Edge::Edge(float weight, int num, int n1, int n2) :
weight(weight),
num(num),
n1(n1),
n2(n2)
{}

bool Edge::operator== (const Edge& edge) const
{
    return num == edge.getNum();
}

float Edge::getWeight() const
{
    return weight;
}

int Edge::getNum() const
{
    return num;
}

int Edge::getN1() const
{
    return n1;
}

int Edge::getN2() const
{
    return n2;
}