//
//  heap.h
//  Scheduler
//

#include "Job.h"
#include <array>
#include <vector>

class ScheduleHeap
{
public:
    // Create empty heap
    ScheduleHeap();
    
    void insert(Job job);
    
    Job extractMax();
    
    void print();
    
    ~ScheduleHeap();
    
private:
    int validPos(int * goodPos, int curPos);
    Job& heapAt(int i);
    void swap(int pos1, int pos2);
    void increaseSize();
    int parent(int pos);
    int leftChild(int pos);
    int rightChild(int pos);
    
    int lastPos;
    int heapLength;
    Job * heap;
};