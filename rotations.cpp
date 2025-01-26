#include "rb-tree.hpp"

void rightRotate(Node *root)
{
    Node *temp = root->left;
    root->left = temp->right;
    if (temp->right != nullptr)
    {
        temp->right->parent = root;
    }
    temp->right = root;
    temp->parent = root->parent;
    root->parent = temp;
}

void leftRotate(Node *root)
{
    Node *temp = root->right;
    root->right = temp->left;
    if (temp->left != nullptr)
    {
        temp->left->parent = root;
    }
    temp->left = root;
    temp->parent = root->parent;
    root->parent = temp;
}