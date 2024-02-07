#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

/*
    ��������� ���� ���������
    ��-22
    ������� 21

    21. �������  ����  �������������  �����.  ��� ������ ������
    �������� ������������ ����� �����, ������� �����  ��������  ��
    ����   ������.   �   �������  ���������  ��������   ����������
    ������������   ����,   �������  �����  ��������  �����   �����
    ���������� �������� (10).

    ����� ����������: CLion 2023.2.2
*/


using namespace std;

const int INF = numeric_limits<int>::max();

int dijkstraMaxCapacity(const vector<vector<int>>& graph, int start, int end, vector<int>& path) {
    int n = graph.size();
    vector<int> Di(n, -1);
    vector<int> Ci(n, 0);  // Change initial Ci to 0
    vector<int> prev(n, -1);

    Ci[start] = INF;

    while (true) {
        int i = -1;
        for (int j = 0; j < n; j++) {
            if (Di[j] == -1 && (i == -1 || Ci[j] > Ci[i])) {
                i = j;
            }
        }

        if (i == -1) {
            break;
        }

        Di[i] = 1;

        for (int j = 0; j < n; j++) {
            if (graph[i][j] > 0) {
                int Mj = min(Ci[i], graph[i][j]);
                if (Mj > Ci[j]) {
                    Ci[j] = Mj;
                    prev[j] = i;
                }
            }
        }
    }

    if (Ci[end] == 0) {
        return 0;
    }

    // �������������� ����
    int current = end;
    while (current != start) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());


    return Ci[end];
}

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream file("input.txt");
    vector<vector<int>> graph;

    if (file.is_open()) {
        string line;
        int max_vertex = 0;

        while (getline(file, line)) {
            istringstream iss(line);
            int from, to, weight;
            iss >> from >> to >> weight;

            max_vertex = max(max_vertex, max(--from, --to));
        }

        graph.resize(max_vertex + 1, vector<int>(max_vertex + 1, 0));

        file.clear();
        file.seekg(0, ios::beg);

        while (getline(file, line)) {
            istringstream iss(line);
            int from, to, weight;
            iss >> from >> to >> weight;
            graph[--from][--to] = weight;
        }

        file.close();

        for (int i = 0; i <= max_vertex; i++) {
            for (int j = 0; j <= max_vertex; j++) {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Unable to open file";
    }

    int start;
    int end;

    cout << "������� ��������� �������: ";
    cin >> start;
    cout << endl;
    start--;

    cout << "������� �������� �������: ";
    cin >> end;
    cout << endl;
    end--;

    vector<int> path;

    int maxCapacity = dijkstraMaxCapacity(graph, start, end, path);

    if (maxCapacity > 0) {
        cout << "������������ ���� �� " << ++start << " � " << ++end << " ����� " << maxCapacity << endl;
        cout << "����: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] + 1;
            if (i != path.size() - 1) {
                cout << "-";
            }
        }
        cout << endl;
    } else {
        cout << "��� ���� �� " << ++start << " � " << ++end << endl;
    }

    return 0;
}
