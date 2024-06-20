#pragma once

#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include "../DataStructures/BinaryTree.h"
using namespace std;

int findIndex(string str, int si, int ei, char openChar, char closeChar);

string treeToString(const ds::Tree<int> *root);

ds::Tree<int> *treeFromString(string str, int si, int ei);

void printBT(const ds::Tree<int> *node);
