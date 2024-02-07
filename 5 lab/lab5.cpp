#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>

/*
    Пайбаршев Глеб Романович
    ПС-22
    Задание 15

    15. Реализовать  эвристический   алгоритм   решения  задачи
    коммивояжера на неориентированном полном  графе  на  основании
    метода  Прима  нахождения  остовного дерева. Проиллюстрировать
    по шагам этапы поиска (11).

    Среда разработки: CLion 2023.2.2
*/

using namespace std;

const int INF = numeric_limits<int>::max();

void printPath(const vector<int> &path) {
    for (int vertex: path) {
        cout << vertex + 1 << "-";
    }
    cout << path[0] + 1 << endl;
}

void printStep(int step, const vector<int> &path, int totalWeight) {
    cout << "Шаг " << step << ": ";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] + 1;
        if (i < path.size() - 1) {
            cout << "-";
        }
    }
    cout << " (Вес: " << totalWeight << ")" << endl;
}

void greedyPrim(const vector<vector<int>> &graph) {
    int graphSize = graph.size();
    vector<int> path;
    vector<bool> visited(graphSize, false);

    int current = 0;
    visited[current] = true;
    path.push_back(current);
    int totalWeight = 0;

    for (int step = 1; step < graphSize; ++step) {
        int minWeight = INF;
        int nextVertex = -1;

        for (int neighbor = 0; neighbor < graphSize; ++neighbor) {
            if (!visited[neighbor] && graph[current][neighbor] < minWeight) {
                minWeight = graph[current][neighbor];
                nextVertex = neighbor;
            }
        }

        visited[nextVertex] = true;
        current = nextVertex;
        path.push_back(current);
        totalWeight += minWeight;

        printStep(step, path, totalWeight);
    }

    cout << "Финальный список: ";
    printPath(path);
    cout << "Итоговый вес: " << totalWeight + graph[current][path[0]] << endl;
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
            graph[to][from] = weight;
        }

        file.close();

        for (int i = 0; i <= max_vertex; i++) {
            for (int j = 0; j <= max_vertex; j++) {
                if ((graph[i][j] / 10) < 1) {
                    cout << graph[i][j] << "  ";
                } else {
                    cout << graph[i][j] << " ";
                }

            }
            cout << endl;
        }
    } else {
        cout << "Невозможно открыть файл";
    }

    greedyPrim(graph);

    return 0;
}
