#include "TreeFunctions.h"

using namespace std;

int findIndexOfClosingChar(const string &str, int startIndex, int endIndex, char openChar, char closeChar, int count = 0)
{
    if (startIndex > endIndex)
        return -1;
    if (str[startIndex] == openChar)
    {
        return findIndexOfClosingChar(str, startIndex + 1, endIndex, openChar, closeChar, count + 1);
    }
    else if (str[startIndex] == closeChar)
    {
        if (count == 1)
        {
            return startIndex;
        }
        else
        {
            return findIndexOfClosingChar(str, startIndex + 1, endIndex, openChar, closeChar, count - 1);
        }
    }
    else
    {
        return findIndexOfClosingChar(str, startIndex + 1, endIndex, openChar, closeChar, count);
    }
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
        index = findIndexOfClosingChar(str, si, ei, '(', ')');
        if (index != -1)
        {
            root->setLeft(treeFromString(str, si + 1, index - 1));
            root->setRight(treeFromString(str, index + 2, ei - 1));
        }
    }

    if (si <= ei && str[si] == '[')
    {
        index = findIndexOfClosingChar(str, si, ei, '[', ']');
        if (index != -1)
        {
            root->setRight(treeFromString(str, si + 1, index - 1));
            root->setLeft(treeFromString(str, index + 2, ei - 1));
        }
    }

    return root;
}
