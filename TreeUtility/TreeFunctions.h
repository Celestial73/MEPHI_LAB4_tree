#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include "../DataStructures/BinaryTree.h"
using namespace std;

// function to return the index of close parenthesis
int findIndex(string str, int si, int ei, char openChar, char closeChar);

string treeToString(const ds::Tree<int> *root);

// function to construct tree from string
ds::Tree<int> *treeFromString(string str, int si, int ei);

void printBT(const ds::Tree<int> *node);
