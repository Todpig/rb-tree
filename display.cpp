#include "rb-tree.hpp"
#include <iostream>
using namespace std;

void preOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    cout << root->value << "(" << (root->color == RED ? "RED" : "BLACK") << ")" << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node *root)
{
    if (root == nullptr)
        return;
    inOrder(root->left);
    cout << root->value << "(" << (root->color == RED ? "RED" : "BLACK") << ")" << " ";
    inOrder(root->right);
}