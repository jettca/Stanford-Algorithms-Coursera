//
//  ScheduleHeap.cpp
//  Scheduler
//

#include "ScheduleHeap.h"
#include <iostream>

using namespace std;

ScheduleHeap::ScheduleHeap() :
lastPos(0),
heapLength(1),
heap(new Job[1])
{}
void ScheduleHeap::insert(Job job)
{
    lastPos++;
    heapAt(lastPos) = job;
    if(lastPos >= heapLength)
        increaseSize();
    
    // Bubble up
    int curPos = lastPos;
    int parentPos = parent(curPos);
    while(parentPos > 0 and heapAt(parentPos) < job)
    {
        swap(curPos, parentPos);
        curPos = parentPos;
        parentPos = parent(curPos);
    }
}

Job ScheduleHeap::extractMax()
{
    Job jobToReturn = heapAt(1);
    swap(1, lastPos);
    lastPos--;
    
    // Bubble down
    int curPos = 1;
    int * goodPos = new int[2];
    int arrSize = validPos(goodPos, curPos);
    
    while(arrSize > 0)
    {
        int maxPos = goodPos[0];
        if(arrSize == 2 and heapAt(maxPos) < heapAt(goodPos[1]))
            maxPos = goodPos[1];
        swap(curPos, maxPos);
        curPos = maxPos;
        arrSize = validPos(goodPos, curPos);
    }
    delete goodPos;
    return jobToReturn;
}

void ScheduleHeap::print()
{
    cout << "Size: " << heapLength << " " << lastPos << "\n";
    for(int i = 0; i < lastPos; i++)
        heap[i].print();
}

int ScheduleHeap::validPos(int * goodPos, int curPos)
{
    int lChild = leftChild(curPos);
    int rChild = rightChild(curPos);
    int arrSize = 0;
    
    if(lChild <= lastPos and heapAt(curPos) < heapAt(lChild))
    {
        goodPos[0] = lChild;
        arrSize++;
    }
    if(rChild <= lastPos and heapAt(curPos) < heapAt(rChild))
    {
        goodPos[arrSize] = rChild;
        arrSize++;
    }
    return arrSize;
}

Job& ScheduleHeap::heapAt(int i)
{
    return heap[i - 1];
}

void ScheduleHeap::swap(int pos1, int pos2)
{
    Job temp = heapAt(pos1);
    heapAt(pos1) = heapAt(pos2);
    heapAt(pos2) = temp;
}

void ScheduleHeap::increaseSize()
{
    Job * nheap = new Job[2*heapLength];
    for(int i = 0; i < heapLength; i++)
    {
        nheap[i] = heap[i];
    }
    Job * oheap = heap;
    heap = nheap;
    heapLength *= 2;
    delete oheap;
}

int ScheduleHeap::parent(int pos)
{
    return pos / 2;
}

int ScheduleHeap::leftChild(int pos)
{
    return pos * 2;
}

int ScheduleHeap::rightChild(int pos)
{
    return pos * 2 + 1;
}

ScheduleHeap::~ScheduleHeap()
{
    delete heap;
}