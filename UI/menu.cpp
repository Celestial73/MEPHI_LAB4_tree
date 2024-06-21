#include <iostream>
#include "menu.h"
#include "../tests/PriorityQueue_tests.h"
#include "../tests/BinaryTree_tests.h"
#include "../TreeUtility/TreeFunctions.h"
#include "PrintFunctions.h"
#include <bits/stdc++.h>
using namespace std;
void menu()
{
    int manageNumber;
    while (true)
    {
        printMainMenu();
        manageNumber = getIntegerInRange(1, 5);
        switch (manageNumber)
        {
        case 1:
            tryTree();
            break;
        case 2:
            tryPriorityQueue();
            break;
        case 3:
            runTests();
            break;
        case 4:
            compareExecutionTimes();
            break;
        case 5:
            return;
        default:
            return;
        }
    }
}

void runTests()
{
    testTree();
    testPriorityQueue();
}

void tryPriorityQueue()
{
    int manageNumber;
    printPriorityQueueOperations();
    manageNumber = getIntegerInRange(1, 3);
    switch (manageNumber)
    {
    case 1:
        queueCreation();
        break;
    case 2:
        queueGetSubsequence();
        break;
    case 3:
        queueFindSubsequence();
        break;
    default:
        return;
    }
}

void tryTree()
{
    int manageNumber;
    printTreeOperations();
    manageNumber = getIntegerInRange(1, 10);
    switch (manageNumber)
    {
    case 1:
        treeCreation();
        break;
    case 2:
        treeCreationFromString();
        break;
    case 3:
        saveTreeToString();
        break;
    case 4:
        treeMap();
        break;
    case 5:
        treeWhere();
        break;
    case 6:
        treeReduce();
        break;
    case 7:
        treeIsFind();
        break;
    case 8:
        treeSubtree();
        break;
    case 9:
        treeDeleteElement();
        break;
    case 10:
        break;
    default:
        return;
    }
}

void queueCreation()
{
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>();
    fillIntegerQueue(queue);
    cout << "The queue is: " << endl;
    printIntegerQueue(queue, queue->getLength());
}

void queueFindSubsequence()
{
    cout << "First create the main queue, where the subqueue will be searched for: " << endl;
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>();
    fillIntegerQueue(queue);
    cout << "The queue is: " << endl;
    printIntegerQueue(queue, queue->getLength());
    cout << "Create the subqueue: " << endl;
    ds::PriorityQueue<int> *subqueue = new ds::PriorityQueue<int>();
    fillIntegerQueue(subqueue);
    cout << "The subqueue is: " << endl;
    printIntegerQueue(subqueue, subqueue->getLength());
    int result = queue->findSubsequence(*subqueue);
    if (result == -1)
    {
        cout << "The subqueue is not present in the queue. " << endl;
    }
    else
    {
        cout << "The subqueue is present in the queue. The first entry starts on the " << result << "th element." << endl;
    }
}
void queueGetSubsequence()
{
    cout << "First create the queue to get the subsequence from: " << endl;
    ds::PriorityQueue<int> *queue = new ds::PriorityQueue<int>();
    fillIntegerQueue(queue);
    cout << "The queue is: " << endl;
    printIntegerQueue(queue, queue->getLength());
    cout << "Enter the start index: " << endl;
    int startIndex = getIntegerInRange(0, queue->getLength() - 1);
    cout << "Enter the end index: " << endl;
    int endIndex = getIntegerInRange(startIndex, queue->getLength() - 1);
    ds::PriorityQueue<int> *subqueue = queue->getSubsequence(startIndex, endIndex);
    cout << "The subqueue is: " << endl;
    printIntegerQueue(subqueue, subqueue->getLength());
    delete queue;
    delete subqueue;
}

void fillIntegerQueue(ds::PriorityQueue<int> *queue)
{
    std::cout << "Enter the integer queue elements. (Input a character when you want to stop)" << std::endl;
    int data;
    int priority;

    std::cout << "Input the data of the element: " << std::endl;
    while (createInteger(&data))
    {
        std::cout << "Input the priority of the element: " << std::endl;
        while (!createInteger(&priority))
        {
            std::cout << "Input the priority of the element: " << std::endl;
        }
        std::cout << "Input the data of the element: " << std::endl;
        queue->push(data, priority);
    }
}

void fillIntegerTree(ds::Tree<int> **destination)
{
    std::cout << "Enter the integer tree elements. The tree balances itself.(Input a character when you want to stop)" << std::endl;
    int number;
    while (createInteger(&number))
    {
        (*destination)->insert(number, destination);
    }
}

void treeCreation()
{
    ds::Tree<int> *tr = nullptr;
    fillIntegerTree(&tr);
    cout << "The tree is: \n";
    printBT(tr);

    delete tr;
}

void treeCreationFromString()
{
    string buffer;
    string formatString;
    cout << "Input a format string in the following way: \n";
    cout << "Root(Left)[Right]" << endl;

    getline(cin, buffer);
    getline(cin, formatString);
    ds::Tree<int> *tr = treeFromString(formatString, 0, formatString.length() - 1);
    cout << "The tree is: \n";
    printBT(tr);
    delete tr;
}
void saveTreeToString()
{
    ds::Tree<int> *tr = nullptr;
    fillIntegerTree(&tr);
    cout << "The tree is: \n";
    printBT(tr);
    string resultString = treeToString(tr);
    cout << "The resulting string is: " << endl;
    cout << resultString << endl;

    cout << "// Try creating a tree from this string (test a tree -> Tree creation from a format string)" << endl;
    delete tr;
}

void treeMap()
{
    cout << "Create an integer tree, and it will be doubled via map method. " << endl;
    ds::Tree<int> *tr = nullptr;
    fillIntegerTree(&tr);
    cout << "The tree is: \n";
    printBT(tr);
    ds::Tree<int> *doubledTree = nullptr;
    tr->map(&doubledTree, tr, multiplyIntBy2);
    cout << "The doubled tree is: \n";
    printBT(doubledTree);
    delete tr;
    delete doubledTree;
}

void treeWhere()
{
    cout << "Create an integer tree, and it will be filtered to have only even numbers via where method. " << endl;
    ds::Tree<int> *tr = nullptr;
    fillIntegerTree(&tr);
    cout << "The tree is: \n";
    printBT(tr);
    ds::Tree<int> *filteredTree = nullptr;
    tr->where(&filteredTree, tr, isEven);
    cout << "The filtered tree is: \n";
    printBT(filteredTree);
    delete tr;
    delete filteredTree;
}

void treeReduce()
{
    cout << "Create an integer tree, and it will be reduced to the sum of it's elements via reduce method. " << endl;
    ds::Tree<int> *tr = nullptr;
    fillIntegerTree(&tr);
    cout << "The tree is: \n";
    printBT(tr);

    int res = 0;
    tr->reduce(res, tr, add);
    cout << "The reduction result is: \n"
         << res << endl;
    delete tr;
}

void treeIsFind()
{
    ds::Tree<int> *tr = createDefaultTree();
    cout << "Here is a simple tree. Input an element to check if it is in the tree." << endl;
    printBT(tr);
    int number;
    createInteger(&number);
    if (tr->isFind(number, tr))
    {
        cout << "The element is in the tree." << endl;
    }
    else
    {
        cout << "The element is not the tree." << endl;
    };
}

void treeSubtree()
{
    ds::Tree<int> *tr = createDefaultTree();
    cout << "Here is a simple tree. Input an element to get a subtree starting from it." << endl;
    printBT(tr);
    int number;
    createInteger(&number);
    if (!(tr->isFind(number, tr)))
    {
        cout << "There is no such element in the tree" << endl;
        return;
    }
    ds::Tree<int> *subtree = nullptr;
    tr->getSubtree(&subtree, tr, number);
    printBT(subtree);
}

void treeDeleteElement()
{
    ds::Tree<int> *tr = createDefaultTree();
    cout << "Here is a simple tree. Input an element to delete." << endl;
    printBT(tr);
    int number;
    createInteger(&number);
    if (!(tr->isFind(number, tr)))
    {
        cout << "There is already no such element in the tree." << endl;
        return;
    }
    tr->deleteElement(number, &tr);
    printBT(tr);
}

int getIntegerInRange(int min, int max)
{
    while (true)
    {
        int number;
        std::cin >> number;
        while (!cin)
        {
            cin.clear();
            cin.ignore();
            continue;
        }
        if (number <= max && number >= min)
        {
            return number;
        }
        cout << "Number out of range" << endl;
    }
}

bool createInteger(int *destination)
{
    std::cin >> *destination;
    if (!cin)
    {
        cin.clear();
        cin.ignore();
        return 0;
    }
    return 1;
}

int createRandomIntNumber(int maxNumber)
{
    return rand() % maxNumber;
}

void compareExecutionTimes()
{
    executionTime(1000);
    executionTime(10000);
    executionTime(100000);
    executionTime(1000000);
    executionTime(10000000);
}

void executionTime(int size)
{
    cout << "Launching tests for a tree of " << size << " items" << endl;
    double creation = creationExecutionTime(size);
    cout << "Creation time : " << fixed
         << creation << setprecision(5);
    cout << " sec " << endl;
    ds::Tree<int> *tr = nullptr;
    for (int i = 0; i < size; i++)
    {
        tr->insert(2, &tr);
    }
    double map = mapExecutionTime(tr);
    cout << "Map time : " << fixed
         << map << setprecision(5);
    cout << " sec " << endl;
    double write = writeToStringExecutionTime(tr);
    cout << "Write to string time : " << fixed
         << write << setprecision(5);
    cout << " sec " << endl
         << endl;
    delete tr;
}

double creationExecutionTime(int size)
{
    time_t startCreation, endCreation;
    ds::Tree<int> *tr = nullptr;
    time(&startCreation);

    ios_base::sync_with_stdio(false);
    for (int i = 0; i < size; i++)
    {
        tr->insert(2, &tr);
    }
    time(&endCreation);
    delete tr;
    return double(endCreation - startCreation);
}

double mapExecutionTime(ds::Tree<int> *tree)
{
    time_t startMap, endMap;
    ds::Tree<int> *newTree = nullptr;
    time(&startMap);
    ios_base::sync_with_stdio(false);
    tree->map(&newTree, tree, multiplyIntBy2);
    time(&endMap);
    delete newTree;
    return double(endMap - startMap);
}

double writeToStringExecutionTime(ds::Tree<int> *tree)
{
    time_t startWrite, endWrite;
    ds::Tree<int> *newTree = nullptr;
    time(&startWrite);
    ios_base::sync_with_stdio(false);
    string result;
    result = treeToString(tree);
    time(&endWrite);
    delete newTree;
    return double(endWrite - startWrite);
}
