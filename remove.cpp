#include "rb-tree.hpp"
#include <iostream>

void fixDoubleBlack(Node *root, Node *node)
{
    if (node == root)
    {
        return;
    }

    Node *sibling = (node->parent->left == node) ? node->parent->right : node->parent->left;
    Node *parent = node->parent;

    if (sibling == nullptr)
    {
        fixDoubleBlack(root, parent);
    }
    else if (sibling->color == RED)
    {
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling == parent->left)
        {
            rightRotate(parent);
        }
        else
        {
            leftRotate(parent);
        }
        fixDoubleBlack(root, node);
    }
    else
    {
        if ((sibling->left != nullptr && sibling->left->color == RED) ||
            (sibling->right != nullptr && sibling->right->color == RED))
        {
            if (sibling->left != nullptr && sibling->left->color == RED)
            {
                if (sibling == parent->left)
                {
                    sibling->left->color = sibling->color;
                    sibling->color = parent->color;
                    rightRotate(parent);
                }
                else
                {
                    sibling->left->color = parent->color;
                    rightRotate(sibling);
                    leftRotate(parent);
                }
            }
            else
            {
                if (sibling == parent->left)
                {
                    sibling->right->color = parent->color;
                    leftRotate(sibling);
                    rightRotate(parent);
                }
                else
                {
                    sibling->right->color = sibling->color;
                    sibling->color = parent->color;
                    leftRotate(parent);
                }
            }
            parent->color = BLACK;
        }
        else
        {
            sibling->color = RED;
            if (parent->color == BLACK)
            {
                fixDoubleBlack(root, parent);
            }
            else
            {
                parent->color = BLACK;
            }
        }
    }
}

Node *findMin(Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

void replaceNode(Node *&root, Node *node, Node *child)
{
    if (node->parent == nullptr)
    {
        root = child;
        if (child != nullptr)
        {
            child->parent = nullptr;
        }
    }
    else
    {
        if (node == node->parent->left)
        {
            node->parent->left = child;
        }
        else
        {
            node->parent->right = child;
        }
        if (child != nullptr)
        {
            child->parent = node->parent;
        }
    }
}

void remove(Node *&root, int value)
{
    if (root == nullptr)
        return;

    Node *node = root;
    Node *parent = nullptr;
    Node *replacement = nullptr;
    Color originalColor;

    while (node != nullptr && node->value != value)
    {
        parent = node;
        if (value < node->value)
            node = node->left;
        else
            node = node->right;
    }

    if (node == nullptr)
    {
        cout << "Value " << value << " not found in the tree." << endl;
        return;
    }

    originalColor = node->color;

    if (node->left == nullptr)
    {
        replacement = node->right;
        replaceNode(root, node, node->right);
    }

    else if (node->right == nullptr)
    {
        replacement = node->left;
        replaceNode(root, node->left, node);
    }

    else
    {
        Node *successor = findMin(node->right);
        originalColor = successor->color;
        replacement = successor->right;

        if (successor->parent != node)
        {
            replaceNode(root, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        else
        {
            if (replacement)
                replacement->parent = successor;
        }

        replaceNode(root, node, successor);
        successor->left = node->left;
        if (node->left)
            node->left->parent = successor;
        successor->color = node->color;
    }

    delete node;

    if (originalColor == BLACK && root != nullptr)
    {
        if (replacement)
            fixDoubleBlack(root, replacement);
        else if (parent)
            fixDoubleBlack(root, parent);
    }

    if (root != nullptr)
        root->color = BLACK;
}
