#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};
struct Node
{
    Node *left;
    Node *right;
    Node *parent;
    Color color;
    int value;
};

bool isEmpty(Node *root);
void preOrder(Node *root);
Node *search(int value, Node *root);
void push(Node *&root, int value);
void readjustColors(Node *root);
void inOrder(Node *root);
void rightRotate(Node *root);
void leftRotate(Node *root);
void fixDoubleBlack(Node *root, Node *node);
void remove(Node *&root, int value);
Node *findMin(Node *node);
void replaceNode(Node *&root, Node *node, Node *child);

#endif