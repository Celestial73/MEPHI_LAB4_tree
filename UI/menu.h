#pragma once

#include "../DataStructures/BinaryTree.h"
#include "../DataStructures/PriorityQueue.h"

void menu();

// Utility
bool createInteger(int *);

void runTests();
void tryTree();
void tryPriorityQueue();

int createRandomIntNumber(int maxNumber);

int getIntegerInRange(int min, int max);

void fillIntegerTree(ds::Tree<int> **destination);
void treeCreation();
void treeCreationFromString();
void saveTreeToString();
void treeMap();
void treeWhere();
void treeReduce();
void treeIsFind();
void treeSubtree();
void treeDeleteElement();

void fillIntegerQueue(ds::PriorityQueue<int> *queue);
void queueCreation();
void queueGetSubsequence();
void queueFindSubsequence();

void executionTime(int size);
double creationExecutionTime(int size);
double mapExecutionTime(ds::Tree<int> *tree);
double writeToStringExecutionTime(ds::Tree<int> *tree);
void compareExecutionTimes();