#pragma once

// no containers

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

        const T &get() const
        {
            return this->data;
        };

        Tree *treeMin()
        {
            return treeMinA(this);
        };
        Tree *treeSuccessor()
        {
            return treeSuccessorA(this);
        };

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

        // bad naming
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

        static void remove(const T &data, Tree **root)
        {
            if (*root == nullptr)
            {
                return;
            }

            if (data < (*root)->data)
            {
                remove(data, &(*root)->left);
            }
            else if (data > (*root)->data)
            {
                remove(data, &(*root)->right);
            }
            else
            {
                if ((*root)->left == nullptr && (*root)->right == nullptr)
                {
                    delete *root;
                    *root = nullptr;
                }
                else if ((*root)->left == nullptr)
                {
                    Tree *temp = *root;
                    *root = (*root)->right;
                    (*root)->parent = temp->parent;
                    temp->right = nullptr;
                    delete temp;
                }
                else if ((*root)->right == nullptr)
                {
                    Tree *temp = *root;
                    *root = (*root)->left;
                    (*root)->parent = temp->parent;
                    temp->left = nullptr;
                    delete temp;
                }
                else
                {
                    Tree *temp = treeMinA((*root)->right);
                    (*root)->data = temp->data;
                    remove(temp->data, &(*root)->right);
                }
            }

            if (*root != nullptr)
            {
                *root = Balance(*root);
            }
        };

    private:
        T data;
        Tree *left;
        Tree *right;
        Tree *parent;
    };
}