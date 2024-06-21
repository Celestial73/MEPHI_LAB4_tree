#include "PriorityQueueFunctions.h"
#include <bits/stdc++.h>
using namespace std;

void printIntegerQueue(ds::PriorityQueue<int> *queue, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << queue->get(i) << " ";
    }
    cout << endl;
}