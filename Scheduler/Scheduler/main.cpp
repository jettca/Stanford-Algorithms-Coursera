//
//  main.cpp
//  Scheduler
//

#include "ScheduleHeap.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[])
{
    ifstream infile("jobs.txt");

    string line;
    getline(infile, line);
    int numJobs = atoi(line.c_str());
    
    ScheduleHeap s;
    
    for(int i = 0; i < numJobs; i++)
    {
        string line;
        getline(infile, line);
        istringstream ss(line);
        
        string weight_s, length_s;
        getline(ss, weight_s, ' ');
        getline(ss, length_s, ' ');
        
        Job job = Job(atoi(weight_s.c_str()), atoi(length_s.c_str()));
        s.insert(job);
    }
    infile.close();
    
    long int weightedCompletions = 0;
    long int timePassed = 0;
    for(int i = 0; i < numJobs; i++)
    {
        Job curJob = s.extractMax();
        timePassed += curJob.getLength();
        weightedCompletions += timePassed*curJob.getWeight();
    }

    cout << weightedCompletions;

    return 0;
}