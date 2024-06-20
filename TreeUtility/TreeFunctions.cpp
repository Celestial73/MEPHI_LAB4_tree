#include "TreeFunctions.h"
using namespace std;

int findIndex(string str, int si, int ei, char openChar, char closeChar)
{
    if (si > ei)
        return -1;

    stack<char> s;

    for (int i = si; i <= ei; i++)
    {

        if (str[i] == openChar)
            s.push(str[i]);

        else if (str[i] == closeChar)
        {
            if (s.top() == openChar)
            {
                s.pop();
                if (s.empty())
                    return i;
            }
        }
    }
    return -1;
}

string treeToString(const ds::Tree<int> *root)
{
    if (!root)
    {
        return "";
    }
    if (!root->getLeft() && !root->getRight())
    {
        return to_string(root->get());
    }
    if (!root->getRight())
    {
        return to_string(root->get()) + "(" + treeToString(root->getLeft()) + ")";
    }
    return to_string(root->get()) + "(" + treeToString(root->getLeft()) + ")[" + treeToString(root->getRight()) + "]";
}

ds::Tree<int> *treeFromString(const string str, int si, int ei)
{
    if (si > ei)
        return NULL;

    int num = 0;
    while (si <= ei && str[si] >= '0' && str[si] <= '9')
    {
        num *= 10;
        num += (str[si] - '0');
        si++;
    }
    ds::Tree<int> *root = new ds::Tree<int>(num);
    int index = -1;
    root->find(10, root);
    if (si <= ei && str[si] == '(')
    {
        index = findIndex(str, si, ei, '(', ')');
        if (index != -1)
        {
            root->setLeft(treeFromString(str, si + 1, index - 1));
            root->setRight(treeFromString(str, index + 2, ei - 1));
        }
    }

    if (si <= ei && str[si] == '[')
    {
        index = findIndex(str, si, ei, '[', ']');
        if (index != -1)
        {
            root->setRight(treeFromString(str, si + 1, index - 1));
            root->setLeft(treeFromString(str, index + 2, ei - 1));
        }
    }

    return root;
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