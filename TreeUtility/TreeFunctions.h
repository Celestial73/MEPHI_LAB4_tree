#pragma once

#include <string>

#include <iostream>
#include "../DataStructures/BinaryTree.h"
using namespace std;

string treeToString(const ds::Tree<int> *root);

ds::Tree<int> *treeFromString(string str, int si, int ei);

void printBT(const ds::Tree<int> *node);
