#include <io.h>
#include <windows.h>
#include <cstdlib>
#include <cctype>
#include <locale.h>
#include <set>
#include <string>
#include <iostream>
#include <fstream>

/*
    Пайбаршев Глеб романович
    ПС-22
    Задание 11

    11. В  файле  записан  текст  стихотворения.  Форматировать
    текст так,  чтобы каждый куплет из 4 строк следовал с одной  и
    той  же  позиции,  начинался  с  прописной буквы и был сдвинут
    относительно предыдущего куплета на 5 позиций вправо или влево
    поочередно (6).

    Среда разработки: Visual Studio Code 1.15.1
*/

using namespace std;

const int maxLineSize = 256;

const int maxIndentSize = 5;

int main()
{
    setlocale(LC_ALL, "Russian");

    string inputTxt;
    string outputTxt;
    int leftIndentCount;

    cout << "Введите имя входного файла ";
    cin >> inputTxt;
    inputTxt = inputTxt + ".txt";
    cout << endl;

    ifstream inputFile(inputTxt);

    if (inputFile.is_open())
    {
        cout << "Введите имя выходного файла ";
        cin >> outputTxt;
        outputTxt = outputTxt + ".txt";
        cout << endl;

        ofstream outputFile(outputTxt);

        cout << "Введите число для левого отступа ";
        cin >> leftIndentCount;
        cout << endl;

        char readCh;
        bool skipSpaces = true;
        bool topRegNextChar = true;
        bool spaceForPharagraph = false;

        string readLine;

        int checkLines = 0;
        int scoreChars = 0;

        string leftIndent;
        string spaceLines;

        set<char> letters_set;

        for (char x = 'A'; x <= 'Z'; ++x)
        {
            letters_set.insert(x);
            letters_set.insert(x + 32);
        }

        for (char y = 'А'; y <= 'Я'; ++y)
        {
            letters_set.insert(y);
            letters_set.insert(y + 32);
        }

        letters_set.insert('ё');
        letters_set.insert('Ё');

        for (int x = 0; x < leftIndentCount; x++)
            leftIndent += " ";

        for (int x = 0; x < maxIndentSize; x++)
            spaceLines += " ";

        while (inputFile.get(readCh))
        {

            if (skipSpaces && (readCh == ' ')) //если пробел
                continue;

            if (readCh != '\n') //если не конец строки
            {
                skipSpaces = false;

                if ((scoreChars == 0) && (letters_set.find(readCh) != letters_set.end()) && (topRegNextChar))
                {
                    if ((readCh >= 'a' && readCh <= 'z') || (readCh >= 'а' && readCh <= 'я'))
                        readCh = readCh - 32;
                    else if (readCh == 'ё')
                        readCh = 'Ё';
                    topRegNextChar = false;
                }

                readLine += readCh;
                scoreChars++;
                continue;
            }

            if ((readCh == '\n') && (readLine.length() != 0)) //если конец строки
            {
                skipSpaces = true;
                checkLines++;

                if (!spaceForPharagraph)
                    outputFile << leftIndent << readLine << endl;
                if (spaceForPharagraph)
                    outputFile << leftIndent << spaceLines << readLine << endl;

                if (checkLines == 4)
                {
                    spaceForPharagraph = !spaceForPharagraph;
                    checkLines = 0;
                }

                readLine = "";
                scoreChars = 0;
                topRegNextChar = true;
                continue;
            }
        }

        inputFile.close();
        outputFile.close();

        cout << "Данные успешно скопированы в файл " << outputTxt << endl;
    }
    else
    {
        cout << "Ошибка открытия входного файла" << endl;
    }

    return 0;
}
