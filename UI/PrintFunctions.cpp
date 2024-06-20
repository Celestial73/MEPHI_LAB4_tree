#include "PrintFunctions.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void printTypes()
{
    cout << "Choose the type" << endl;
    cout << "Enter 1 - Int" << endl;
    cout << "Enter 2 - Complex" << endl;
};

void printMainMenu()
{
    cout << "Enter 1 - test a tree" << endl;
    cout << "Enter 2 - run tests" << endl;
    cout << "Enter 3 - compare execution times for sets of different sizes" << endl;
    cout << "Enter 4 - cancel" << endl;
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

void printInteger(int number)
{
    cout << std::setfill(' ') << std::setw(4) << number << " ";
}