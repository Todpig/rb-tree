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

void displayTree(Node *currentRoot, int indent = 0)
{
    if (currentRoot == nullptr)
    {
        return;
    }
    indent += 7;
    displayTree(currentRoot->right, indent);
    cout << string(indent, ' ') << currentRoot->value << "(" << (currentRoot->color == RED ? "RED" : "BLACK") << ")" << endl;
    displayTree(currentRoot->left, indent);
}

int main()
{
    Node *root = nullptr;
    push(root, 100);
    push(root, 50);
    push(root, 200);
    push(root, 70);
    push(root, 140);
    push(root, 30);
    push(root, 350);
    push(root, 117);
    push(root, 400);
    push(root, 42);
    push(root, 80);
    push(root, 65);
    push(root, 10);
    push(root, 20);
    push(root, 9);
    displayTree(root);
    return 0;
}
