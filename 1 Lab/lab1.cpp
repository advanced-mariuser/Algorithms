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
    ��������� ���� ���������
    ��-22
    ������� 11

    11. �  �����  �������  �����  �������������.  �������������
    ����� ���,  ����� ������ ������ �� 4 ����� �������� � �����  �
    ���  ��  �������,  ���������  �  ��������� ����� � ��� �������
    ������������ ����������� ������� �� 5 ������� ������ ��� �����
    ���������� (6).

    ����� ����������: Visual Studio Code 1.15.1
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

    cout << "������� ��� �������� ����� ";
    cin >> inputTxt;
    inputTxt = inputTxt + ".txt";
    cout << endl;

    ifstream inputFile(inputTxt);

    if (inputFile.is_open())
    {
        cout << "������� ��� ��������� ����� ";
        cin >> outputTxt;
        outputTxt = outputTxt + ".txt";
        cout << endl;

        ofstream outputFile(outputTxt);

        cout << "������� ����� ��� ������ ������� ";
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

        for (char y = '�'; y <= '�'; ++y)
        {
            letters_set.insert(y);
            letters_set.insert(y + 32);
        }

        letters_set.insert('�');
        letters_set.insert('�');

        for (int x = 0; x < leftIndentCount; x++)
            leftIndent += " ";

        for (int x = 0; x < maxIndentSize; x++)
            spaceLines += " ";

        while (inputFile.get(readCh))
        {

            if (skipSpaces && (readCh == ' ')) //���� ������
                continue;

            if (readCh != '\n') //���� �� ����� ������
            {
                skipSpaces = false;

                if ((scoreChars == 0) && (letters_set.find(readCh) != letters_set.end()) && (topRegNextChar))
                {
                    if ((readCh >= 'a' && readCh <= 'z') || (readCh >= '�' && readCh <= '�'))
                        readCh = readCh - 32;
                    else if (readCh == '�')
                        readCh = '�';
                    topRegNextChar = false;
                }

                readLine += readCh;
                scoreChars++;
                continue;
            }

            if ((readCh == '\n') && (readLine.length() != 0)) //���� ����� ������
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

        cout << "������ ������� ����������� � ���� " << outputTxt << endl;
    }
    else
    {
        cout << "������ �������� �������� �����" << endl;
    }

    return 0;
}
