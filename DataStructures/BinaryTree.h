#pragma once

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

        static void insert(const T &data, Tree **root, Tree *parent = nullptr)
        {
            if (*root == nullptr)
            {
                *root = new Tree(data, nullptr, nullptr, parent);
                return;
            }

            if (data > (*root)->data)
            {
                insert(data, &((*root)->right), *root);
            }
            else
            {
                insert(data, &((*root)->left), *root);
            }

            *root = Balance(*root);
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

            if (areIdentical(candidate, root))
            {
                return true;
            }
            return isSubtree(root->left, candidate) || isSubtree(root->right, candidate);
        }

        static bool areIdentical(Tree *root1, Tree *root2)
        {
            if (root1 == nullptr && root2 == nullptr)
            {
                return true;
            }

            if (root1 == nullptr || root2 == nullptr)
            {
                return false;
            }

            return (root1->data == root2->data && areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right));
        }

        static void reduce(T &result, Tree *root, T (*BinaryOperation)(T, T))
        {
            if (root == nullptr)
                return;

            result = BinaryOperation(root->data, result);

            reduce(result, root->left, BinaryOperation);
            reduce(result, root->right, BinaryOperation);
        };

        static int count(Tree *root)
        {
            if (root == nullptr)
                return 0;

            int l = count(root->left);
            int r = count(root->right);

            return l + r + 1;
        };

        static Tree *treeMin(Tree *item)
        {
            if (item == nullptr)
            {
                return nullptr;
            }
            while (item->left != nullptr)
            {
                item = item->left;
            }
            return item;
        };

        static Tree *treeSuccessor(Tree *item)
        {
            if (item == nullptr)
            {
                return nullptr;
            }
            if (item->right != nullptr)
            {
                return item->right->treeMin(item->right);
            }

            Tree *parent = item->parent;
            // go up the ladder
            // once the item will not be to the right of the parent, the parent will be the item's successor
            while (parent != nullptr && item == parent->right)
            {
                item = parent;
                parent = parent->parent;
            }

            return parent;
        };
        static void deleteElement(const T &data, Tree **root)
        {
            if (*root == nullptr)
                return;

            if (data < (*root)->data)
                deleteElement(data, &(*root)->left);

            else if (data > (*root)->data)
                deleteElement(data, &(*root)->right);

            else
            {
                // case 1: no children -> remove the node
                if ((*root)->left == nullptr && (*root)->right == nullptr)
                {
                    delete *root;
                    *root = nullptr;
                }
                // case 2: one child -> replace the node with the child
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
                // case 3: both children -> find its in-order successor,
                // replace the node's value with the successor's value, and delete the successor.
                else
                {
                    Tree *temp = treeMin((*root)->right);
                    (*root)->data = temp->data;
                    deleteElement(temp->data, &(*root)->right);
                }
            }
            *root = Balance(*root);
        }

        static Tree *Balance(Tree *tr)
        {
            if (factor(tr) < -1)
            {
                if (factor(tr->right) <= 0)
                {
                    tr = leftRotation(tr);
                }

                else
                {
                    tr = extendedLeftRotation(tr);
                }
            }
            if (factor(tr) > 1)
            {
                if (factor(tr->left) >= 0)
                {
                    tr = rightRotation(tr);
                }

                else
                {
                    tr = extendedRightRotation(tr);
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

            if (root->left == nullptr)
                leftHeight = 0;
            else
                leftHeight = height(root->left);

            if (root->right == nullptr)
                rightHeight = 0;
            else
                rightHeight = height(root->right);

            if (leftHeight > rightHeight)
            {
                return (leftHeight + 1);
            }
            return (rightHeight + 1);
        };

        void rootLeftRightTraversal(Tree *root, void (*handleElement)(T))
        {
            if (root != nullptr)
            {
                handleElement(root->data);
                rootLeftRightTraversal(root->left, handleElement);
                rootLeftRightTraversal(root->right, handleElement);
            }
        }
        void rootRightLeftTraversal(Tree *root, void (*handleElement)(T))
        {
            if (root != nullptr)
            {
                handleElement(root->data);
                rootLeftRightTraversal(root->right, handleElement);
                rootLeftRightTraversal(root->left, handleElement);
            }
        }
        void leftRightRootTraversal(Tree *root, void (*handleElement)(T))
        {
            if (root != nullptr)
            {
                rootLeftRightTraversal(root->left, handleElement);
                rootLeftRightTraversal(root->right, handleElement);
                handleElement(root->data);
            }
        }
        void leftRootRightTraversal(Tree *root, void (*handleElement)(T))
        {
            if (root != nullptr)
            {
                rootLeftRightTraversal(root->left, handleElement);
                handleElement(root->data);
                rootLeftRightTraversal(root->right, handleElement);
            }
        }
        void rightLeftRootTraversal(Tree *root, void (*handleElement)(T))
        {
            if (root != nullptr)
            {
                rootLeftRightTraversal(root->right, handleElement);
                rootLeftRightTraversal(root->left, handleElement);
                handleElement(root->data);
            }
        }
        void rightRootLeftTraversal(Tree *root, void (*handleElement)(T))
        {
            if (root != nullptr)
            {
                rootLeftRightTraversal(root->right, handleElement);
                handleElement(root->data);
                rootLeftRightTraversal(root->left, handleElement);
            }
        }

        const T &get() const
        {
            return this->data;
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

        // difference between left and right subtree heights
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

        static Tree *extendedLeftRotation(Tree *root)
        {
            root->right = rightRotation(root->right);
            root = leftRotation(root);

            return root;
        };
        static Tree *extendedRightRotation(Tree *root)
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