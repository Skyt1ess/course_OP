#include <iostream>
using namespace std;

const int MAX_E = (int) 1e6;
const int MAX_V = (int) 1e3;
const int INF   = (int) 1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
    // Прямое ребро
    onEnd[edgeCount] = v;                   // на конце прямого v
    nextEdge[edgeCount] = firstEdge[u];     // добавляем в начало списка для u
    firstEdge[u] = edgeCount;               // теперь начало списка - новое ребро
    capacity[edgeCount++] = cap;            // устанавливаем пропускную способность
    // Обратное ребро
    onEnd[edgeCount] = u;                   // на конце обратного u
    nextEdge[edgeCount] = firstEdge[v];     // добавляем в начало списка для v
    firstEdge[v] = edgeCount;               // теперь начало списка - новое ребро
    capacity[edgeCount++] = 0;              // устанавливаем пропускную способность
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; // возвращяем полученный минимум на пути
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, min(flow, capacity[edge])); // ищем поток в поддереве
            if (minResult > 0) {                    // если нашли
                capacity[edge]      -= minResult;   // у прямых ребер вычетаем поток
                capacity[edge ^ 1]  += minResult;   // к обратным прибавляем
                return minResult;   
            }
        }
    }
    return 0; // если не нашли поток из этой вершины вернем 0
}

int main() {
    fill(firstEdge, firstEdge + MAX_V, -1);     // -1 означает ребра нет
    cin >> numOfVertex >> numOfEdge;            // считываем количество вершин и ребер
    cin >> sourceVertex >> destinationVertex;   // считываем источник и сток
    for (int i = 0, u, v, cap; i < numOfEdge; i++) {
        cin >> u >> v >> cap;
        addEdge(u, v, cap);
    }
    // Нахождение максимального потока
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
        fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    // Выводим максимальный поток
    cout << maxFlow << endl;
    return 0;
}
