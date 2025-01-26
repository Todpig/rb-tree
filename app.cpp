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

    cout << "Árvore inicial:\n";
    preOrder(root);

    cout << "\nRemovendo nó 70 (vermelho, com filhos):\n";
    remove(root, 70);
    preOrder(root);
    cout << endl;

    cout << "\nRemovendo nó 100 (raiz, negro):\n";
    remove(root, 100);
    preOrder(root);
    cout << endl;

    cout << "\nRemovendo nó 9 (vermelho, sem filhos):\n";
    remove(root, 9);
    preOrder(root);
    cout << endl;

    cout << "\nRemovendo nó 350 (negro, com filho):\n";
    remove(root, 350);
    cout << "Árvore após remover 350:\n";
    preOrder(root);
    cout << endl;

    cout << "Verificando todos os nós restantes:\n";
    preOrder(root);
    cout << endl;

    return 0;
}

void printInOrder(Node *root)
{
    if (root == nullptr)
        return;
    printInOrder(root->left);
    cout << root->value << " ";
    printInOrder(root->right);
}
