#include "BinaryTree_tests.h"
#include <iostream>
#include <time.h>
#include "../TreeUtility/TreeFunctions.h"

void checkDefaultTree(ds::Tree<int> *tr)
{
    IS_TRUE(tr != nullptr);
    IS_TRUE(tr->getLeft() != nullptr);
    IS_TRUE(tr->getRight() != nullptr);
    IS_TRUE(tr->getLeft()->getLeft() != nullptr);
    IS_TRUE(tr->getLeft()->getRight() != nullptr);

    IS_TRUE(tr->get() == 10);
    IS_TRUE(tr->getLeft()->get() == 8);
    IS_TRUE(tr->getRight()->get() == 12);
    IS_TRUE(tr->getLeft()->getLeft()->get() == 7);
    IS_TRUE(tr->getLeft()->getRight()->get() == 9);
    IS_TRUE(tr->height(tr) == 3);
}

int add(int x, int y)
{
    return x + y;
}

void testGetSubtree()
{
    ds::Tree<int> *tr = createDefaultTree();
    ds::Tree<int> *subtree = nullptr;
    tr->getSubtree(&subtree, tr, 8);
    IS_TRUE(subtree->get() == 8);
    IS_TRUE(subtree->getLeft()->get() == 7);
    IS_TRUE(subtree->getRight()->get() == 9);
    std::cout << "Tree get subtree tested" << std::endl;
    delete tr;
    delete subtree;
}

void testTreeReduce()
{
    ds::Tree<int> *tr = createDefaultTree();
    int res = 0;
    tr->reduce(res, tr, add);
    IS_TRUE(res == 46);
    std::cout << "Tree reduce tested" << std::endl;
    delete tr;
}

int multiplyIntBy2(int value)
{
    return value * 2;
}

void testTreeMap()
{
    ds::Tree<int> *tr = createDefaultTree();
    ds::Tree<int> *mappedTree = nullptr;
    tr->map(&mappedTree, tr, multiplyIntBy2);

    IS_TRUE(mappedTree->get() == 16);
    IS_TRUE(mappedTree->getLeft()->get() == 14);
    IS_TRUE(mappedTree->getRight()->get() == 20);
    IS_TRUE(mappedTree->height(tr) == 3);
    std::cout << "Tree map tested" << std::endl;
    delete tr;
    delete mappedTree;
}

bool isEven(int value)
{
    return (value % 2 == 0);
}

void testTreeWhere()
{
    ds::Tree<int> *tr = createDefaultTree();
    ds::Tree<int> *filteredTree = nullptr;
    tr->where(&filteredTree, tr, isEven);
    IS_TRUE(filteredTree->get() == 10);
    IS_TRUE(filteredTree->getLeft()->get() == 8);
    IS_TRUE(filteredTree->getRight()->get() == 12);
    std::cout << "Tree where tested" << std::endl;
    delete tr;
    delete filteredTree;
}

void testIsSubtree()
{
    ds::Tree<int> *tr = createDefaultTree();
    ds::Tree<int> *wrongTree = nullptr;
    wrongTree->insert(12, &wrongTree);
    wrongTree->insert(8, &wrongTree);
    IS_TRUE(!(wrongTree->isSubtree(tr, wrongTree)));
    ds::Tree<int> *correctTree = nullptr;
    correctTree->insert(8, &correctTree);
    correctTree->insert(7, &correctTree);
    correctTree->insert(9, &correctTree);
    IS_TRUE(correctTree->isSubtree(tr, correctTree));
    std::cout << "Tree isSubtree tested" << std::endl;
    delete tr;
    delete wrongTree;
}

ds::Tree<int> *createDefaultTree()
{
    ds::Tree<int> *tr = nullptr;

    tr->insert(10, &tr);
    tr->insert(8, &tr);
    tr->insert(12, &tr);
    tr->insert(7, &tr);
    tr->insert(9, &tr);
    return tr;
}

void testTreeCreationFromString()
{
    string treeString = "10(8(7)[9])[12]";
    ds::Tree<int> *tr = treeFromString(treeString, 0, treeString.size() - 1);
    checkDefaultTree(tr);
    std::cout << "Tree creationFromString tested" << std::endl;
    delete tr;
}

void testStringCreationFromString()
{
    string treeString;
    ds::Tree<int> *tr = createDefaultTree();
    treeString = treeToString(tr);
    IS_TRUE(treeString == "10(8(7)[9])[12]")
    std::cout << "Tree stringFromTree tested" << std::endl;
    delete tr;
}

void testTreeInsert()
{

    ds::Tree<int> *tr = createDefaultTree();
    checkDefaultTree(tr);
    std::cout << "Tree insert tested" << std::endl;
    delete tr;
}

void testTreeDelete()
{
    ds::Tree<int> *tr = createDefaultTree();
    IS_TRUE(tr->isFind(9, tr));
    tr->deleteElement(9, &tr);
    IS_TRUE(!(tr->isFind(9, tr)));
    tr->deleteElement(10, &tr);
    IS_TRUE(tr->get() == 8);

    std::cout << "Tree delete tested" << std::endl;
    delete tr;
}

void testTreeFind()
{
    ds::Tree<int> *tr = createDefaultTree();
    ds::Tree<int> *eightNode = tr->find(8, tr);
    IS_TRUE(eightNode->getLeft()->get() == 7);
    IS_TRUE(eightNode->getRight()->get() == 9);
    IS_TRUE(eightNode->getParent()->get() == 10);
    std::cout << "Tree find tested" << std::endl;
    delete tr;
}

void testTreeHeight()
{
    ds::Tree<int> *tr = nullptr;
    for (int i = 0; i < 1023; i++)
    {
        tr->insert(10, &tr);
    }
    IS_TRUE(tr->height(tr) == 10);
    tr->insert(10, &tr);
    IS_TRUE(tr->height(tr) == 11);
    std::cout << "Tree height tested" << std::endl;
    delete tr;
}

void testTreeIsFind()
{
    ds::Tree<int> *tr = nullptr;
    for (int i = 0; i < 1023; i++)
    {
        tr->insert(10, &tr);
    }
    IS_TRUE(!(tr->isFind(11, tr)));
    tr->insert(11, &tr);
    IS_TRUE(tr->isFind(11, tr));
    std::cout << "Tree isFind tested" << std::endl;
    delete tr;
}

void testTreeCreation()
{
    srand((unsigned)time(NULL));
    ds::Tree<int> *tr = nullptr;
    for (int i = 0; i < 20; i++)
    {
        int n = 100;
        tr->insert(rand() % n, &tr);
    }
    printBT(tr);

    std::cout << "The height is: " << tr->height(tr) << std::endl;
    std::cout << "Tree creation tested" << std::endl;
    delete tr;
}

void testTree()
{
    testTreeHeight();
    testTreeInsert();
    testTreeDelete();
    testTreeIsFind();
    testTreeFind();
    testTreeMap();
    testTreeWhere();
    testTreeReduce();
    testGetSubtree();
    testIsSubtree();
    testTreeCreationFromString();
    testStringCreationFromString();
    std::cout << "TREE TESTED" << std::endl;
}