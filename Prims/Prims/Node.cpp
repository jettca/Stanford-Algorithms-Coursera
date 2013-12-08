//
//  Node.cpp
//  Prims
//

#include "Node.h"
#include <iostream>

using namespace std;

Node::Node() :
num(-1),
minEdge(Edge())
{}

Node::Node(int num) :
num(num),
minEdge(Edge())
{}

Node::Node(int num, Edge e) :
num(num),
minEdge(e)
{}

int Node::getNum() const
{
    return num;
}

float Node::getKey() const
{
    return minEdge.getWeight();
}

Edge Node::getEdge() const
{
    return minEdge;
}

void Node::setMinEdge(Edge edge)
{
    minEdge = edge;
}

bool Node::operator== (const Node& node) const
{
    return num == node.getNum();
}

bool Node::operator< (const Node& node) const
{
    return getKey() < node.getKey();
}

void Node::print() const
{
    cout << getKey() << " " << num << endl;
}