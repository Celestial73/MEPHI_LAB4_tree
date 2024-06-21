#pragma once
#include "BinaryTree.h"
using namespace std;

namespace ds
{
    template <class T>
    class PriorityQueue;

    template <class T>
    class Node
    {
        T data;
        int priority;

    public:
        Node(const T &data, const T &priority) : data(data), priority(priority){};

        bool operator==(const Node &other) const
        {
            return (this->data == other.data &&
                    this->priority == other.priority);
        }

        bool operator!=(const Node &other) const
        {
            return (this->data != other.data ||
                    this->priority != other.priority);
        }

        bool operator>(const Node &other) const
        {
            return (this->priority < other.priority);
        }
        bool operator<(const Node &other) const
        {
            return (this->priority > other.priority);
        }

        friend class PriorityQueue<T>;
    };

    // template <class T, T (*Transf)(T value)>
    // Node<T> mapNode(Node<T> node)
    // {
    //     return Node(Transf(node.data), node.priority);
    // }

    template <class T>
    class PriorityQueue
    {
    private:
        Tree<Node<T>> *tree;

    public:
        PriorityQueue() : tree(nullptr){};

        PriorityQueue(const T &data, const T &priority) : tree(nullptr)
        {

            tree->insert(Node<T>(data, priority), &tree);
        }

        ~PriorityQueue()
        {
            delete tree;
        }

        int getLength() const
        {
            return tree->count(tree);
        }

        const T &peek() const
        {
            if (tree == nullptr)
                // Usually i throw an instance of std::invalid_argument
                // But it is in <iostream>
                // Can <iostream> be included for this purpose?
                throw "accessing empty tree";
            return tree->treeMin(tree)->get().data;
        }

        T pop()
        {
            Tree<Node<T>> *temp = tree->treeMin(tree);
            T value = temp->get().data;
            tree->deleteElement(temp->get(), &tree);
            return value;
        }

        const T &get(int index) const
        {
            Tree<Node<T>> *traverseNode = tree->treeMin(tree);
            for (int i = 0; i < index; i++)
            {
                traverseNode = traverseNode->treeSuccessor(traverseNode);
            }
            return traverseNode->get().data;
        }

        void push(int data, int priority)
        {
            Node<T> temp = Node(data, priority);
            tree->insert(temp, &tree);
        }

        bool isEmpty()
        {
            return tree == nullptr;
        }

        // returns -1 if subsequence is not found
        // else returns the index where the entry starts
        int findSubsequence(const PriorityQueue<int> &candidate)
        {
            int thisSize = getLength();
            int candidateSize = candidate.getLength();

            for (int i = 0; i <= thisSize - candidateSize; i++)
            {
                int j;

                for (j = 0; j < candidateSize; j++)
                {
                    if (get(i + j) != candidate.get(j))
                        break;
                }

                if (j == candidateSize)
                    return i;
            }

            return -1;
        }

        PriorityQueue *getSubsequence(int start, int end)
        {
            if (start < 0 || end >= getLength() || start > end)
            {
                throw "Invalid argument";
            }
            if (tree == nullptr)
            {
                throw "EmptyTree";
            }
            Tree<Node<T>> *traverseNode = tree->treeMin(tree);
            PriorityQueue *subSequence = new PriorityQueue();
            for (int i = 0; i < start; i++)
            {
                traverseNode = traverseNode->treeSuccessor(traverseNode);
            }
            for (; end > start; end--)
            {
                subSequence->push(traverseNode->get().data, traverseNode->get().priority);
                traverseNode = traverseNode->treeSuccessor(traverseNode);
            }
            return subSequence;
        }
    };

}
