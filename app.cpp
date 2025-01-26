#include "rb-tree.hpp"
#include <random>

void menu(Node *&root)
{
    int choice;
    do
    {
        cout << "\nMenu de opções:\n";
        cout << "1. Gerar arvore aleatória\n";
        cout << "2. Inserir valor\n";
        cout << "3. Remover valor\n";
        cout << "4. Exibir em ordem\n";
        cout << "5. Exibir em pré-ordem\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Saindo...\n";
            break;
        case 1:
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> sizeDist(5, 15);
            uniform_int_distribution<> valueDist(1, 100);

            int treeSize = sizeDist(gen);
            cout << "Gerando uma árvore com " << treeSize << " valores aleatórios...\n";

            for (int i = 0; i < treeSize; i++)
            {
                int randomValue = valueDist(gen);
                push(root, randomValue);
            }

            break;
        }
        case 2:
        {
            int value;
            cout << "Digite o valor a ser inserido: ";
            cin >> value;
            push(root, value);
            break;
        }
        case 3:
        {
            int value;
            cout << "Digite o valor a ser removido: ";
            cin >> value;
            remove(root, value);
            break;
        }
        case 4:
            cout << "Exibindo em ordem:\n";
            inOrder(root);
            cout << endl;
            break;
        case 5:
            cout << "Exibindo em pré-ordem:\n";
            preOrder(root);
            cout << endl;
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
            break;
        }
    } while (choice != 0);
}

int main()
{
    Node *root = nullptr;
    menu(root);
    return 0;
}