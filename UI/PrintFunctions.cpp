#include "PrintFunctions.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printMainMenu()
{
    cout << "Enter 1 - test a tree" << endl;
    cout << "Enter 2 - test a priority queue" << endl;
    cout << "Enter 3 - run tests" << endl;
    cout << "Enter 4 - compare execution times for sets of different sizes" << endl;
    cout << "Enter 5 - cancel" << endl;
};

void printTreeOperations()
{

    cout << "What do you want to test?" << endl;
    cout << "Enter 1 - Tree creation" << endl;
    cout << "Enter 2 - Tree creation from a format string" << endl;
    cout << "Enter 3 - Writing a tree into a format string" << endl;
    cout << "Enter 4 - Map method" << endl;
    cout << "Enter 5 - Where method" << endl;
    cout << "Enter 6 - Reduce method" << endl;
    cout << "Enter 7 - Finding if an element is present in a tree" << endl;
    cout << "Enter 8 - Getting a subtree" << endl;
    cout << "Enter 9 - Deletion of an element" << endl;
}

void printPriorityQueueOperations()
{

    cout << "What do you want to test?" << endl;
    cout << "Enter 1 - Queue creation" << endl;
    cout << "Enter 2 - Getting a subsequence of a queue" << endl;
    cout << "Enter 3 - Finding a subsequence if present" << endl;
}

void printInteger(int number)
{
    cout << std::setfill(' ') << std::setw(4) << number << " ";
}

void printIntegerQueue(ds::PriorityQueue<int> *queue, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << queue->get(i) << " ";
    }
    cout << endl;
}

void printBinaryTree(const std::string &prefix, const ds::Tree<int> *tr, bool isLeft)
{
    if (tr != nullptr)
    {
        printBinaryTree(prefix + "     ", tr->getRight(), false);
        std::cout << (prefix + ("|-- ")) << tr->get() << endl;
        printBinaryTree(prefix + "     ", tr->getLeft(), true);
    }
}

void printBT(const ds::Tree<int> *tree)
{
    printBinaryTree("", tree, false);
}

void printInt(int i)
{
    std::cout << i << " ";
}
