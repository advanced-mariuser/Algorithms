#include <iostream>
#include <string>
#include <locale.h>
#include <cstdlib>

/*
    ��������� ���� ���������
    ��-22
    ������� 20

    20. ������������  � ��������  ������  � ������� ����������
    �������  ��  ������. ����������  ��������  �������  �����  ��
    ������  �������, ����������  �  �����������  �������,  ������
    ����������� ������� (9).

    ����� ����������: Visual Studio Code 1.15.1
*/

using namespace std;

const string SEPARATOR = "=============================================";
const string SEPARATOR_STACK = "+++++++++++++++++++++++++++++++++++++++++++++";

struct Stack
{
    int key;
    Stack *nextStack;
};

struct Node
{
    Stack *data;
    Node *nextNode;
};

struct Queue
{
    int size;           // ������� ������� �������
    Node *firstElement; // ��������� �� ������ ������� �������
    Node *lastElement;  // ��������� �� ��������� ������� �������
};

//Stack============================================================================
void push(Stack *&S, int stackElement) // ��������� � ����
{
    Stack *temp = new Stack;
    temp->key = stackElement;
    temp->nextStack = S;
    S = temp;
    cout << S->key;

    cout << "\n"
         << SEPARATOR_STACK << endl;
    cout << "           ������� ����� ��������" << endl;
    cout << SEPARATOR_STACK << endl;
}

void pop(Stack *&S) // �������� �� �����
{
    if (S != nullptr)
    {
        Stack *temp = S;
        S = S->nextStack;
        delete temp;

        cout << "\n"
             << SEPARATOR << endl;
        cout << "          ������� ����� ������" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "          ���� ����" << endl;
        cout << SEPARATOR << endl;
    }
}

void showStack(Stack *S) // ����� ����������� ����� �� �����
{
    Stack *temp = S;
    cout << "\n"
         << SEPARATOR_STACK << endl;
    cout << "+              �������� �����:\n";
    while (temp)
    {
        cout << "+                    [" << temp->key << "]\n";
        temp = temp->nextStack;
    }
    cout << SEPARATOR_STACK << endl;
}

void clearStack(Stack *&S) // ������� �����
{
    while (S)
    {
        Stack *temp = S;
        S = S->nextStack;
        delete temp;
    }
    cout << "\n"
         << SEPARATOR_STACK << endl;
    cout << "            ���� ������� ������" << endl;
    cout << SEPARATOR_STACK << endl;
}

//Queue==========================================================================
void creationQueue(Queue *&Q) // �������� �������
{
    Q->firstElement = new Node;
    Q->firstElement->nextNode = nullptr;
    Q->lastElement = Q->firstElement;
    Q->size = 0;
}

void addQueue(Queue *&Q, Stack *queueElement, int number) // ��������� � �������
{
    if (queueElement)
    {
        Q->lastElement->nextNode = new Node;
        Q->lastElement = Q->lastElement->nextNode;
        Q->lastElement->data = queueElement;
        Q->lastElement->nextNode = nullptr;
        Q->size++;
        cout << "\n"
             << SEPARATOR << endl;
        cout << "              ������� ��������" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                ���� ����" << endl;
        cout << SEPARATOR << endl;
    }
}

void removeQueue(Queue *&Q) // �������� �� �������
{
    if (Q->firstElement->nextNode != nullptr)
    {
        Node *temp = Q->firstElement;
        Q->firstElement = temp->nextNode;
        delete temp;
        Q->size--;

        cout << "\n"
             << SEPARATOR << endl;
        cout << "               ������� ������" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                ������� �����" << endl;
        cout << SEPARATOR << endl;
    }
}

void showQueue(Queue *Q) // ����� ����������� ������� �� �����
{
    if (Q->size > 0)
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "�������� �������:\n";
        Node *temp = Q->firstElement->nextNode;
        int i = Q->size - 1;
        while (temp)
        {
            cout << "\n           "
                 << "[" << Q->size - i << "-� ������� �������]";
            showStack((temp->data));
            temp = temp->nextNode;
            i--;
        }
        cout << "\n"
             << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                ������� �����" << endl;
        cout << SEPARATOR << endl;
    }
}

void clearQueue(Queue *&Q) // ������� �������
{
    if (Q->firstElement->nextNode != nullptr)
    {
        while (Q->firstElement->nextNode)
        {
            Node *temp = Q->firstElement->nextNode;
            Q->firstElement->nextNode = temp->nextNode;
            delete temp;
        }
        Q->lastElement = Q->firstElement;
        cout << "\n"
             << SEPARATOR << endl;
        cout << "������� ������� �������" << endl;
        cout << SEPARATOR << endl;
    }
}

void editQueue(Queue *&Q) //�������������� �������� �������
{
    if (Q->firstElement != nullptr && Q->firstElement->nextNode != nullptr)
    {
        Stack *top = Q->firstElement->nextNode->data;
        int answer3 = 1;
        while (answer3 != 5)
        {
            showStack(top);
            cout << "\n1) ��������� � ����";
            cout << "\n2) �������� �� �����";
            cout << "\n3) ������ �����";
            cout << "\n4) �������� ����� �����";
            cout << "\n5) ������� � �������";
            cout << "\n��� �����? ";

            cin >> answer3;

            system("cls");
            switch (answer3)
            {
            case 1: // ��������� � ����
                int k;
                cout << "������� ����� ����� ";
                cin >> k;
                push(top, k);
                break;
            case 2: // �������� �� �����
                if (top)
                    pop(top);
                else
                {
                    cout << "\n"
                         << SEPARATOR_STACK << endl;
                    cout << "                  ���� ����\n";
                    cout << SEPARATOR_STACK << endl;
                }
                break;
            case 3: // ����� �� �����
                if (top)
                    showStack(top);
                else
                {
                    cout << "\n"
                         << SEPARATOR_STACK << endl;
                    cout << "                  ���� ����\n";
                    cout << SEPARATOR_STACK << endl;
                }
                break;
            case 4: // ������� �����
                if (top)
                {
                    clearStack(top);
                }
                else
                {
                    cout << "\n"
                         << SEPARATOR_STACK << endl;
                    cout << "                  ���� ����\n";
                    cout << SEPARATOR_STACK << endl;
                }
                top = nullptr; // ������� clear �� ���������� top!
                break;
            case 5:
                if (!top)
                {
                    removeQueue(Q);
                }
                else
                {
                    Q->firstElement->nextNode->data = top;
                    cout << "new Top";
                }
            }
        }
        cout << "\n"
             << SEPARATOR << endl;
        cout << "������� ������� ������� ��������������" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                ������� �����" << endl;
        cout << SEPARATOR << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("cls");
    Queue *Q = new Queue;
    creationQueue(Q);

    int answer = 0;
    int iter = 0;
    int number = 0;
    while (answer != 6)
    {
        cout << "\n1) ��������� � �������";
        cout << "\n2) �������� �� �������";
        cout << "\n3) ������ ����������� �������";
        cout << "\n4) ������� �������";
        cout << "\n5) ������������� ������ ������� �������";
        cout << "\n6) �����";
        cout << "\n��� �����? ";

        cin >> answer;

        system("cls");
        switch (answer)
        {
        case 1: // ��������� � �������
        {
            Stack *top = 0; // ������� ��������� �� Stack � �������������� ��� ��������� nullptr
            iter++;
            int answer1 = 1;
            while (answer1 != 5)
            {
                cout << "\n1) ��������� � ����";
                cout << "\n2) �������� �� �����";
                cout << "\n3) ������ �����";
                cout << "\n4) �������� ����� �����";
                cout << "\n5) ������� � �������";
                cout << "\n��� �����? ";

                cin >> answer1;

                system("cls");
                switch (answer1)
                {
                case 1: // ��������� � ����
                    int k;
                    cout << "������� ����� ����� ";
                    cin >> k;
                    push(top, k);
                    break;
                case 2: // �������� �� �����
                    if (top)
                        pop(top);
                    else
                    {
                        cout << "\n"
                             << SEPARATOR_STACK << endl;
                        cout << "                  ���� ����\n";
                        cout << SEPARATOR_STACK << endl;
                    }
                    break;
                case 3: // ����� �� �����
                    if (top)
                        showStack(top);
                    else
                    {
                        cout << "\n"
                             << SEPARATOR_STACK << endl;
                        cout << "                  ���� ����\n";
                        cout << SEPARATOR_STACK << endl;
                    }
                    break;
                case 4: // ������� �����
                    if (top)
                    {
                        clearStack(top);
                    }
                    else
                    {
                        cout << "\n"
                             << SEPARATOR_STACK << endl;
                        cout << "                  ���� ����\n";
                        cout << SEPARATOR_STACK << endl;
                    }
                    top = 0; // ������� clear �� ���������� top!
                    break;
                }
            }
            addQueue(Q, top, iter);
            break;
        }
        case 2: // �������� �� �������
            removeQueue(Q);
            break;
        case 3: // ������ ����������� �������
            showQueue(Q);
            break;
        case 4: // ������� �������
            clearQueue(Q);
            break;
        case 5: // �������������� �������
            editQueue(Q);
            showQueue(Q);
            break;
        }
    }

    return 0;
}
