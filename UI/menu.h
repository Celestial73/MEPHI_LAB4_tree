#pragma once

#include "../DataStructures/BinaryTree.h"
#include "../tests/BinaryTree_tests.h"
#include "../TreeUtility/TreeFunctions.h"
#include "PrintFunctions.h"

void menu();

// Utility
bool createInteger(int *);

void runTests();
void tryTree();

int createRandomIntNumber(int maxNumber);

int getIntegerInRange(int min, int max);

void treeCreation();
void treeCreationFromString();
void saveTreeToString();
void treeMap();
void treeWhere();
void treeReduce();
void treeIsFind();
void treeSubtree();
void treeDeleteElement();

void executionTime(int size);
double creationExecutionTime(int size);
double mapExecutionTime(ds::Tree<int> *tree);
double writeToStringExecutionTime(ds::Tree<int> *tree);
void compareExecutionTimes();