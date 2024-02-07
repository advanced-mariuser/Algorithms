#include <iostream>
#include <string>
#include <stack>
#include <fstream>

/*
    Пайбаршев Глеб Романович
    ПС-22
    Задание 22

    22. Имеется некоторое  алгебраическое выражение.  Операнды
    заданы идентификаторами,  операции выполняются по приоритетам,
    допускается использование круглых скобок. Возможны одноместные
    операции '+' и '-', а также операция возведения в степень '^'.
    Требуется построить и выдать в наглядном виде бинарное дерево,
    представляющее данное выражение (12).

    Среда разработки: CLion 2023.2.2
*/

using namespace std;

//===============================================================================================

string skipExtraSpaces(string expression) {
    string tempExpression;
    for (char i: expression) {
        if (i == ' ') {
            continue;
        }
        tempExpression += i;
    }
    return tempExpression;
}

string removeExtraBrackets(const string &expression) {
    string result = expression;
    while (result.front() == '(' && result.back() == ')') {
        int count = 0;
        bool found = false;
        for (int i = 0; i < result.size() - 1; i++) {
            if (result[i] == '(') {
                count++;
            } else if (result[i] == ')') {
                count--;
            }
            if (count == 0 && i < result.size() - 2) {
                found = true;
                break;
            }
        }
        if (!found) {
            result = result.substr(1, result.size() - 2);
        } else {
            break;
        }
    }
    return result;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int getPriority(char oper) {
    if (oper == '+' || oper == '-') {
        return 1;
    } else if (oper == '*' || oper == '/') {
        return 2;
    } else if (oper == '^') {
        return 3;
    }
    return 0;
}

void findUnaryMinus(std::string& expression, int start) {
    if (expression[start] == '-'){
        expression[start] = '$';
    }
}


int findMinimalOperation(std::string& expression, int start, int end) {
    findUnaryMinus(expression, start);

    std::stack<char> operators;
    int minimalIndex = -1;
    int parenCount = 0;

    for (int i = end; i >= start; i--) {
        if (expression[i] == ')') {
            parenCount++;
        } else if (expression[i] == '(') {
            parenCount--;
        } else if (parenCount == 0 && isOperator(expression[i])) {
            if (expression[i] == '-' || expression[i] == '+') {
                cout << "minOper(- +) " << expression[i] << endl;
                return i;
            }
        }
    }

    parenCount = 0;

    for (int i = end; i >= start; i--) {
        if (expression[i] == ')') {
            parenCount++;
        } else if (expression[i] == '(') {
            parenCount--;
        } else if (parenCount == 0 && isOperator(expression[i])) {
            if (expression[i] == '*' || expression[i] == '/') {
                cout << "minOper(* /) " << expression[i] << endl;
                return i;
            }
        }
    }

    parenCount = 0;

    for (int i = start; i <= end; i++) {
        if (expression[i] == ')') {
            parenCount++;
        } else if (expression[i] == '(') {
            parenCount--;
        } else if (parenCount == 0 && isOperator(expression[i])) {
            if (expression[i] == '^') {
                cout << "minOper(^) " << expression[i] << endl;
                return i;
            }
        }
    }

    cout << "minOper(minInd) " << expression[minimalIndex] << endl;
    return minimalIndex;
}


//===============================================================================================

struct Node {
    char data;
    Node *left;
    Node *right;
    int level;

    Node(char _data, int _level, Node *_left, Node *_right): data(_data), level(_level), left(_left), right(_right) {}
};

Node *splitExpression(string &expression, int start, int end, int level) {
    int minimalOperation = findMinimalOperation(expression, start, end);
    cout << "Слева: " << expression.substr(start, minimalOperation - 1) << endl;
    cout << "Справа: " << expression.substr(minimalOperation + 1, end) << endl;
    if (minimalOperation != -1) {
        Node *left = splitExpression(expression, start, minimalOperation - 1, level + 1);
        Node *right = splitExpression(expression, minimalOperation + 1, end, level + 1);
        return new Node(expression[minimalOperation], level, left, right);
    } else if (expression[start] == '(' && expression[end] == ')') {
        return splitExpression(expression, start + 1, end - 1, level);
    } else {
        if (expression[start] == '$') {
            expression[start] = '-';
            Node *left;

            if (expression[start + 1] == '(') {
                left = splitExpression(expression, start + 1, end, level + 1);
            } else {
                left = new Node(expression[start + 1], level + 1, nullptr, nullptr);
            }
            return new Node(expression[start], level, left, nullptr);
        }

        return new Node(expression[start], level, nullptr, nullptr);
    }
}

void printTree(Node *tree, std::ofstream &fileOutput) {
    if (tree == nullptr) {
        return;
    }

    printTree(tree->left, fileOutput);
    for (int i = 0; i < tree->level; i++) {
        std::cout << "    ";
        fileOutput << "    ";
    }
    std::cout << tree->data << std::endl;
    fileOutput << tree->data << std::endl;
    printTree(tree->right, fileOutput);
}

//===============================================================================================

int main() {
    setlocale(LC_ALL, "Russian");

    string fileNameInput;

    cout << "Введите название файла: ";
    cin >> fileNameInput;
    fileNameInput += ".txt";

    ifstream fileInput(fileNameInput);
    if (!fileInput.is_open()) {
        cerr << "Ошибка открытия входного файла" << endl;
        return 1;
    }

    ofstream fileOutputClear("output.txt", ios::trunc);
    if (!fileOutputClear.is_open()) {
        cerr << "Ошибка открытия выходного файла" << endl;
        return 1;
    }
    fileOutputClear.close();

    ofstream fileOutput("output.txt", ios::app);
    if (!fileOutput.is_open()) {
        cerr << "Ошибка открытия выходного файла" << endl;
        return 1;
    }

    char readCh;
    string expression;
    while (fileInput.get(readCh)) {
        expression += readCh;
    }

    expression = skipExtraSpaces(expression);
    expression = removeExtraBrackets(expression);
    Node *root = splitExpression(expression, 0, expression.size() - 1, 0);
    printTree(root, fileOutput);
    return 0;
}
