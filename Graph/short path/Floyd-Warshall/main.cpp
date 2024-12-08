/*
input value example
4 7
0 1 5
0 3 7
1 0 4
1 2 -3
2 0 6
2 3 4
3 2 2
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    // 그래프이자 비용
    vector<vector<int>> graph(n, vector<int>(n, 1e9));
    for (int i = 0 ; i < n; i++) {
        graph[i][i] = 0;
    }

    for (int i = 0; i < e; i++) {
        int v, u, weight;
        cin >> v >> u >> weight;

        graph[v][u] = weight;
        // graph[u][v] = weight;    무방향 그래프일 때
    }

    // floyd-warshall 알고리즘. 시간복잡도 n^3
    // 각 지정에서의 최단경로 만듦. 가중치 상관 안함
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}