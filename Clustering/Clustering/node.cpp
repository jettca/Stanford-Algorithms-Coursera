//
//  node.cpp
//  Clustering
//

#include "node.h"

node::node() :
n(-1),
leadptr(nullptr)
{}

node::node(unsigned int num) :
n(num),
leadptr(nullptr)
{}

void node::setLeader(const node * nptr)
{
    leadptr = nptr;
}

bool node::operator== (const node& cmpr) const
{
    return n == cmpr.num();
}

int node::num() const
{
    return n;
}

const node * node::leader() const
{
    return leadptr;
}