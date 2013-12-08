//
//  vertex.cpp
//  APSP
//

#include "vertex.h"
#include <iostream>

vertex::vertex() :
n(0)
{}

vertex::vertex(long num) :
n(num)
{
    if(num <= 0)
    {
        std::cout << "Warning: Num must be greater than 0.  Setting to 0.\n";
        n = 0;
    }
}

unsigned long vertex::num() const
{
    return n;
}

bool vertex::operator== (const vertex& v) const
{
    return n == v.num();
}