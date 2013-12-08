//
//  Job.cpp
//  Scheduler
//

#include "Job.h"
#include <iostream>

using namespace std;

Job::Job() :
weight(-1), length(-1)
{}

Job::Job(int weight, int length) :
weight(weight),
length(length)
{}

int Job::getLength() const
{
    return length;
}

int Job::getWeight() const
{
    return weight;
}

void Job::print()
{
    cout << weight << " " << length << " " << weight - length << endl;
}

bool Job::operator< (const Job &job) const
{
    return compareVal() < job.compareVal();
}

bool Job::operator== (const Job &job) const
{
    return length == job.getLength() and weight == job.getWeight();
}

bool Job::operator> (const Job &job) const
{
    return not (*this < job or *this == job);
}

float Job::compareVal() const
{
    return (float)weight/length;
}