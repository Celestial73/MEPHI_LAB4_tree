#pragma once

#include "../DataStructures/PriorityQueue.h"
#include <string>
void printMainMenu();

void printInteger(int);
void printTreeOperations();
void printPriorityQueueOperations();
void printIntegerQueue(ds::PriorityQueue<int> *queue, int size);
void printBinaryTree(const std::string &prefix, const ds::Tree<int> *tr, bool isLeft);

void printBT(const ds::Tree<int> *tree);
void printInt(int i);
