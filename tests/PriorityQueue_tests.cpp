#include "../DataStructures/PriorityQueue.h"
#include <iostream>
#include "../tests/TestMacros.h"
#include "../PriorityQueueUtility/PriorityQueueFunctions.h"

void testGet()
{
    const int data = 123;
    const int priority = 4;
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>(data, priority);
    IS_TRUE(queue->get(0) == 123);
    queue->push(10, 2);
    queue->push(12, 5);
    queue->push(19, 11);
    printIntegerQueue(queue, queue->getLength());
    IS_TRUE(queue->get(3) == 10);
    IS_TRUE(queue->get(2) == 123);
    IS_TRUE(queue->get(1) == 12);
    IS_TRUE(queue->get(0) == 19);
    delete queue;
    std::cout << "Priority Queue get tested" << std::endl;
}

void testPop()
{
    const int data = 1;
    const int priority = 3;
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>(data, priority);
    IS_TRUE(queue->pop() == 1);
    delete queue;
    std::cout << "Priority Queue pop tested" << std::endl;
}
void testPeek()
{
    const int data = 1;
    const int priority = 3;
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>(data, priority);
    std::cout << queue->peek() << std::endl;
    IS_TRUE(queue->peek() == 1);
    delete queue;
    std::cout << "Priority Queue peek tested" << std::endl;
}

void testPush()
{
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>();
    int c = 99;
    for (int i = 0; i < 10; i++)
    {
        queue->push(c - i, i);
    }
    queue->push(10, 2);
    queue->push(12, 5);
    queue->push(19, 11);
    IS_TRUE(queue->peek() == 19);
    delete queue;
    std::cout << "Priority Queue push tested" << std::endl;
}

void testGetSubsequence()
{
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>();
    int c = 1;
    for (int i = 0; i < 10; i++)
    {
        queue->push(c + i, i);
    }
    ds::PriorityQueue<int> *subqueue = queue->getSubsequence(2, 5);

    IS_TRUE(subqueue->get(0) == 8);
    IS_TRUE(subqueue->get(1) == 7);
    IS_TRUE(subqueue->get(2) == 6);
    delete queue;
    std::cout
        << "Priority Queue getSubsequence tested" << std::endl;
}

void testPriorityQueue()
{

    testPop();
    testPush();
    testPeek();
    testGet();
    testGetSubsequence();
    std::cout << "Priority Queue tested" << std::endl;
};