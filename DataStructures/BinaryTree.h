#pragma once
#include <queue>
#include <bits/stdc++.h>
#include <iostream>
namespace ds
{

    template <class T>
    class Tree
    {
    public:
        Tree(T data, Tree *_left = nullptr, Tree *_right = nullptr, Tree *_parent = nullptr) : data(data), left(_left), right(_right), parent(_parent) {}
        ~Tree()
        {
            {
                if (this == nullptr)
                {
                    return;
                }
                this->left->~Tree();
                this->right->~Tree();
            }
        }

        const Tree *getLeft() const
        {
            return this->left;
        }
        const Tree *getRight() const
        {
            return this->right;
        }
        const Tree *getParent() const
        {
            return this->parent;
        }
        void setLeft(Tree *newLeft)
        {
            left = newLeft;
        }
        void setRight(Tree *newRight)
        {
            right = newRight;
        }
        void setParent(Tree *newParent)
        {
            parent = newParent;
        }

        // insertA(data, this) is not used because
        // the origin root of the tree may change after balancing.
        // Thus the pointer in the driver code may need to be updated.

        // For this reasons many methods are made static, and the user
        // needs to pass a pointer to a pointer to their tree.

        static void insert(const T &data, Tree **root)
        {
            insertA(data, root);
        }

        static Tree *find(const T &data, Tree *root)
        {
            if (root == nullptr)
            {
                return nullptr;
            }

            if (root->data == data)
            {
                return root;
            }

            if (data > root->data)
            {
                return find(data, root->right);
            }
            else
            {
                return find(data, root->left);
            }
        }

        static bool isFind(const T &data, Tree *root)
        {
            if (find(data, root))
            {
                return true;
            }
            else
            {
                return false;
            }
        };

        static void where(Tree **newTree, Tree *root, bool (*Check)(T))
        {
            if (root == nullptr)
            {
                return;
            }

            if (Check(root->data))
            {
                insert(root->data, newTree);
            }

            where(newTree, root->left, Check);
            where(newTree, root->right, Check);
        };

        static void map(Tree **newTree, Tree *root, T (*Transf)(T))
        {
            if (root == nullptr)
            {
                return;
            }

            insert(Transf(root->data), newTree);

            map(newTree, root->left, Transf);
            map(newTree, root->right, Transf);
        };

        static void getSubtree(Tree **newTree, Tree *root, const T &data)
        {
            Tree *item = find(data, root);
            copyTree(newTree, item);
        }

        static int isSubtree(Tree *root, Tree *candidate)
        {
            if (candidate == nullptr)
            {
                return true;
            }

            if (root == nullptr)
            {
                return false;
            }

            if (areEqual(candidate, root))
            {
                return true;
            }
            return isSubtree(root->left, candidate) || isSubtree(root->right, candidate);
        }

        static bool areEqual(Tree *root1, Tree *root2)
        {
            if (root1 == NULL && root2 == NULL)
            {
                return true;
            }

            if (root1 == NULL || root2 == NULL)
            {
                return false;
            }

            return (root1->data == root2->data && areEqual(root1->left, root2->left) && areEqual(root1->right, root2->right));
        }

        static void reduce(T &result, Tree *root, T (*BinaryOperation)(T, T))
        {
            if (root == nullptr)
                return;

            result = BinaryOperation(root->data, result);

            reduce(result, root->left, BinaryOperation);
            reduce(result, root->right, BinaryOperation);
        };

        const T &get() const
        {
            return this->data;
        };
        int count(Tree *root)
        {
            if (root == nullptr)
                return 0;

            int l = count(root->left);
            int r = count(root->right);

            return l + r + 1;
        };

        Tree *treeMin()
        {
            return treeMinA(this);
        };
        Tree *treeSuccessor()
        {
            return treeSuccessorA(this);
        };
        static Tree *deleteTree(const T &data, Tree **root)
        {
            Tree *item = (*root)->find(data, *root);
            if (!item)
            {
                return *root;
            }
            if (item->left == nullptr && item->right == nullptr)
            {
                if (item == *root)
                {
                    delete (*root);
                    *root = nullptr;
                    return nullptr;
                }

                Tree *parent = item->parent;

                if (parent->right == item)
                {
                    parent->right = nullptr;
                }
                else
                {
                    parent->left = nullptr;
                }

                delete (item);

                while (parent != nullptr)
                {
                    parent->right = Balance(parent->right);
                    parent->left = Balance(parent->left);
                    parent = parent->parent;
                }
                *root = Balance(*root);
                return parent;
            }

            if (item->left == nullptr || item->right == nullptr)
            {
                if (item == *root)
                {
                    if (item->left != nullptr)
                    {
                        *root = item->left;
                    }
                    else
                    {
                        *root = item->right;
                    }

                    delete (item);

                    (*root)->parent = nullptr;

                    return nullptr;
                }

                Tree *parent = item->parent;
                Tree *child = nullptr;

                if (item->left != nullptr)
                {
                    child = item->left;
                }
                else
                {
                    child = item->right;
                }

                child->parent = parent;

                if (parent->left == item)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }

                delete (item);

                while (child != nullptr)
                {
                    child->right = Balance(child->right);
                    child->left = Balance(child->left);
                    child = child->parent;
                }
                *root = Balance(*root);
                return parent;
            }

            Tree *fin = item->treeSuccessor();
            Tree *x = nullptr;

            if (fin->left != nullptr)
            {
                x = fin->left;
            }
            else
            {
                x = fin->right;
            }

            if (x != nullptr)
            {
                x->parent = fin->parent;
            }

            if (fin->parent == nullptr)
            {
                *root = x;
            }
            else
            {
                if (fin->parent->left == fin)
                {
                    fin->parent->left = x;
                }
                else
                {
                    fin->parent->right = x;
                }
            }

            if (fin != item)
            {
                item->data = std::move(fin->data);
            }

            Tree *balance = fin->parent;
            delete (fin);

            // for (; balance != nullptr;balance = balance->parent)
            while (balance != nullptr)
            {
                balance->right = Balance(balance->right);
                balance->left = Balance(balance->left);
                balance = balance->parent;
            }
            *root = Balance(*root);
            return item;
        };

        static Tree *Balance(Tree *tr)
        {
            // the right subtree is heavier -> need to rotate to the left
            if (factor(tr) < -1)
            {
                // if the right subtree of the subtree is heavier or the tree is balanced:
                // left rotation

                // If the left subtree of tr->right is 1 or more point taller, we need to rotate tr->right to the right and then make a left rotation on tr
                // Otherwise in the resulting tree the left subtree will be taller

                if (factor(tr->right) <= 0)
                {
                    tr = leftRotation(tr);
                }

                else
                {
                    tr = bLeftRotation(tr);
                }
            }

            // Same logic, symmetrically reversed
            if (factor(tr) > 1)
            {
                if (factor(tr->left) >= 0)
                {
                    tr = rightRotation(tr);
                }

                else
                {
                    tr = bRrightRotation(tr);
                }
            }
            return tr;
        };

        static int height(Tree *root)
        {
            if (root == nullptr)
            {
                return -1;
            }
            int leftHeight, rightHeight;
            // if (root->left == nullptr)
            // {
            //     leftHeight = 0;
            // }
            // else
            // {
            //     // cout << "nonempty left height" << endl;
            //     leftHeight = height(root->left);
            // }
            root->left == nullptr ? leftHeight = 0 : leftHeight = height(root->left);
            root->right == nullptr ? rightHeight = 0 : rightHeight = height(root->right);

            if (leftHeight > rightHeight)
            {
                return (leftHeight + 1);
            }
            else
            {
                return (rightHeight + 1);
            }
        };

    private:
        static void copyTree(Tree **newTree, Tree *root)
        {
            if (root == nullptr)
            {
                return;
            }
            insert(root->data, newTree);

            copyTree(newTree, root->left);
            copyTree(newTree, root->right);
        }

        static void insertA(const T &data, Tree **root, Tree *parent = nullptr)
        {
            if (*root == nullptr)
            {
                *root = new Tree(data, nullptr, nullptr, parent);
                return;
            }

            if (data > (*root)->data)
            {
                insertA(data, &((*root)->right), *root);
            }
            else
            {
                insertA(data, &((*root)->left), *root);
            }

            *root = Balance(*root);
        };

        static Tree *treeMinA(Tree *item)
        {
            while (item->left != nullptr)
            {
                item = item->left;
            }
            return item;
        };

        static Tree *treeSuccessorA(Tree *item)
        {
            if (item->right != nullptr)
            {
                return item->right->treeMin();
            }

            Tree *p = item->parent;
            // go up the ladder
            // once the item will not be to the right of the parent, the parent will be the item's successor
            while (p != nullptr && item == p->right)
            {
                item = p;
                p = p->parent;
            }

            return p;
        };

        static int factor(Tree *root)
        {
            if (root == nullptr)
            {
                return -1;
            }
            return height(root->left) - height(root->right);
        };

        static Tree *rightRotation(Tree *root)
        {
            Tree *l = root->left;
            root->left = l->right;
            l->right = root;

            l->parent = root->parent;
            root->parent = l;
            if (root->left != nullptr)
            {
                root->left->parent = root;
            }

            return l;
        };
        static Tree *leftRotation(Tree *root)
        {
            Tree *r = root->right;
            root->right = r->left;
            r->left = root;

            r->parent = root->parent;
            root->parent = r;
            if (root->right != nullptr)
            {
                root->right->parent = root;
            }

            return r;
        };
        static Tree *bLeftRotation(Tree *root)
        {
            root->right = rightRotation(root->right);
            root = leftRotation(root);

            return root;
        };
        static Tree *bRrightRotation(Tree *root)
        {
            root->left = leftRotation(root->left);
            root = rightRotation(root);

            return root;
        };

    private:
        T data;
        Tree *left;
        Tree *right;
        Tree *parent;
    };
}