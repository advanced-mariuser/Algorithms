#include <iostream>
#include <string>
#include <locale.h>
#include <cstdlib>

/*
    Пайбаршев Глеб романович
    ПС-22
    Задание 20

    20. Организовать  в основной  памяти  с помощью указателей
    очередь  из  стеков. Обеспечить  операции  ведения  стека  из
    начала  очереди, дополнения  и  продвижения  очереди,  выдачи
    содержимого очереди (9).

    Среда разработки: Visual Studio Code 1.15.1
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
    int size;           // счетчик размера очереди
    Node *firstElement; // указатель на первый элемент очереди
    Node *lastElement;  // указатель на последний элемент очереди
};

//Stack============================================================================
void push(Stack *&S, int stackElement) // включение в стек
{
    Stack *temp = new Stack;
    temp->key = stackElement;
    temp->nextStack = S;
    S = temp;
    cout << S->key;

    cout << "\n"
         << SEPARATOR_STACK << endl;
    cout << "           Элемент стека добавлен" << endl;
    cout << SEPARATOR_STACK << endl;
}

void pop(Stack *&S) // удаление из стека
{
    if (S != nullptr)
    {
        Stack *temp = S;
        S = S->nextStack;
        delete temp;

        cout << "\n"
             << SEPARATOR << endl;
        cout << "          Элемент стека удален" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "          Стек пуст" << endl;
        cout << SEPARATOR << endl;
    }
}

void showStack(Stack *S) // вывод содержимого стека на экран
{
    Stack *temp = S;
    cout << "\n"
         << SEPARATOR_STACK << endl;
    cout << "+              Элементы стека:\n";
    while (temp)
    {
        cout << "+                    [" << temp->key << "]\n";
        temp = temp->nextStack;
    }
    cout << SEPARATOR_STACK << endl;
}

void clearStack(Stack *&S) // очистка стека
{
    while (S)
    {
        Stack *temp = S;
        S = S->nextStack;
        delete temp;
    }
    cout << "\n"
         << SEPARATOR_STACK << endl;
    cout << "            Стек успешно очищен" << endl;
    cout << SEPARATOR_STACK << endl;
}

//Queue==========================================================================
void creationQueue(Queue *&Q) // создание очереди
{
    Q->firstElement = new Node;
    Q->firstElement->nextNode = nullptr;
    Q->lastElement = Q->firstElement;
    Q->size = 0;
}

void addQueue(Queue *&Q, Stack *queueElement, int number) // включение в очередь
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
        cout << "              Элемент добавлен" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                Стек пуст" << endl;
        cout << SEPARATOR << endl;
    }
}

void removeQueue(Queue *&Q) // удаление из очереди
{
    if (Q->firstElement->nextNode != nullptr)
    {
        Node *temp = Q->firstElement;
        Q->firstElement = temp->nextNode;
        delete temp;
        Q->size--;

        cout << "\n"
             << SEPARATOR << endl;
        cout << "               Элемент удален" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                Очередь пуста" << endl;
        cout << SEPARATOR << endl;
    }
}

void showQueue(Queue *Q) // вывод содержимого очереди на экран
{
    if (Q->size > 0)
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "Элементы очереди:\n";
        Node *temp = Q->firstElement->nextNode;
        int i = Q->size - 1;
        while (temp)
        {
            cout << "\n           "
                 << "[" << Q->size - i << "-й элемент очереди]";
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
        cout << "                Очередь пуста" << endl;
        cout << SEPARATOR << endl;
    }
}

void clearQueue(Queue *&Q) // очистка очереди
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
        cout << "Очередь успешно очищена" << endl;
        cout << SEPARATOR << endl;
    }
}

void editQueue(Queue *&Q) //редактирование элемента очереди
{
    if (Q->firstElement != nullptr && Q->firstElement->nextNode != nullptr)
    {
        Stack *top = Q->firstElement->nextNode->data;
        int answer3 = 1;
        while (answer3 != 5)
        {
            showStack(top);
            cout << "\n1) Включение в стек";
            cout << "\n2) Удаление из стека";
            cout << "\n3) Выдача стека";
            cout << "\n4) Удаление всего стека";
            cout << "\n5) Возврат к очереди";
            cout << "\nВаш выбор? ";

            cin >> answer3;

            system("cls");
            switch (answer3)
            {
            case 1: // Включение в стек
                int k;
                cout << "Введите целое число ";
                cin >> k;
                push(top, k);
                break;
            case 2: // Удаление из стека
                if (top)
                    pop(top);
                else
                {
                    cout << "\n"
                         << SEPARATOR_STACK << endl;
                    cout << "                  Стек пуст\n";
                    cout << SEPARATOR_STACK << endl;
                }
                break;
            case 3: // Вывод на экран
                if (top)
                    showStack(top);
                else
                {
                    cout << "\n"
                         << SEPARATOR_STACK << endl;
                    cout << "                  Стек пуст\n";
                    cout << SEPARATOR_STACK << endl;
                }
                break;
            case 4: // Очистка стека
                if (top)
                {
                    clearStack(top);
                }
                else
                {
                    cout << "\n"
                         << SEPARATOR_STACK << endl;
                    cout << "                  Стек пуст\n";
                    cout << SEPARATOR_STACK << endl;
                }
                top = nullptr; // функция clear не возвращает top!
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
        cout << "Элемент очереди успешно отредактирован" << endl;
        cout << SEPARATOR << endl;
    }
    else
    {
        cout << "\n"
             << SEPARATOR << endl;
        cout << "                Очередь пуста" << endl;
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
        cout << "\n1) Включение в очередь";
        cout << "\n2) Удаление из очереди";
        cout << "\n3) Выдача содержимого очереди";
        cout << "\n4) Очистка очереди";
        cout << "\n5) Редактировать первый элемент очереди";
        cout << "\n6) Конец";
        cout << "\nВаш выбор? ";

        cin >> answer;

        system("cls");
        switch (answer)
        {
        case 1: // Включение в очередь
        {
            Stack *top = 0; // Создаем указатель на Stack и инициализируем его значением nullptr
            iter++;
            int answer1 = 1;
            while (answer1 != 5)
            {
                cout << "\n1) Включение в стек";
                cout << "\n2) Удаление из стека";
                cout << "\n3) Выдача стека";
                cout << "\n4) Удаление всего стека";
                cout << "\n5) Возврат к очереди";
                cout << "\nВаш выбор? ";

                cin >> answer1;

                system("cls");
                switch (answer1)
                {
                case 1: // Включение в стек
                    int k;
                    cout << "Введите целое число ";
                    cin >> k;
                    push(top, k);
                    break;
                case 2: // Удаление из стека
                    if (top)
                        pop(top);
                    else
                    {
                        cout << "\n"
                             << SEPARATOR_STACK << endl;
                        cout << "                  Стек пуст\n";
                        cout << SEPARATOR_STACK << endl;
                    }
                    break;
                case 3: // Вывод на экран
                    if (top)
                        showStack(top);
                    else
                    {
                        cout << "\n"
                             << SEPARATOR_STACK << endl;
                        cout << "                  Стек пуст\n";
                        cout << SEPARATOR_STACK << endl;
                    }
                    break;
                case 4: // Очистка стека
                    if (top)
                    {
                        clearStack(top);
                    }
                    else
                    {
                        cout << "\n"
                             << SEPARATOR_STACK << endl;
                        cout << "                  Стек пуст\n";
                        cout << SEPARATOR_STACK << endl;
                    }
                    top = 0; // функция clear не возвращает top!
                    break;
                }
            }
            addQueue(Q, top, iter);
            break;
        }
        case 2: // Удаление из очереди
            removeQueue(Q);
            break;
        case 3: // Выдача содержимого очереди
            showQueue(Q);
            break;
        case 4: // Очистка очереди
            clearQueue(Q);
            break;
        case 5: // редактирование очереди
            editQueue(Q);
            showQueue(Q);
            break;
        }
    }

    return 0;
}
