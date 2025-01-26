#include "rb-tree.hpp"
#include <iostream>
using namespace std;

bool isEmpty(Node *root)
{
    return (root == nullptr);
}

Node *search(int value, Node *root)
{
    Node *current = root;
    Node *parent = nullptr;

    while (current != nullptr)
    {
        parent = current;

        if (value == current->value)
        {
            cout << "Value " << value << " already exists in the tree.\n";
            return nullptr;
        }

        if (value > current->value)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }

    return parent;
}

void readjustColors(Node *root)
{
    if (root->parent == nullptr)
    {
        root->color = BLACK;
    }
    else if (root->parent->color == RED)
    {
        Node *grandparent = root->parent->parent;
        Node *uncle = (grandparent->left == root->parent) ? grandparent->right : grandparent->left;

        if (uncle != nullptr && uncle->color == RED)
        {
            root->parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            readjustColors(grandparent);
        }
        else
        {
            if (grandparent->left == root->parent)
            {
                if (root->parent->left == root)
                {
                    root->parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
                else
                {
                    leftRotate(root->parent);
                    root->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            }
            else
            {
                if (root->parent->right == root)
                {
                    root->parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
                else
                {
                    rightRotate(root->parent);
                    root->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            }
        }
    }
}

void push(Node *&root, int value)
{
    if (isEmpty(root))
    {
        root = new Node();
        root->value = value;
        root->color = BLACK;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
        return;
    }
    Node *parent = search(value, root);
    if (parent != nullptr)
    {
        Node *newNode = new Node();
        newNode->value = value;
        newNode->color = RED;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = parent;

        if (value > parent->value)
        {
            parent->right = newNode;
        }
        else
        {
            parent->left = newNode;
        }

        readjustColors(newNode);
    }
}
