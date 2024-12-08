/*
input value example
7 10
0 1 6
0 2 5
0 3 5
1 4 -1
2 1 -2
2 4 1
3 2 -2
3 5 -1
4 6 3
5 3 6

expected: 0 1 3 5 0 4 3
*/
#include <iostream>
#include <vector>

#define INF 1e9

using namespace std;

struct Edge {
    int to;
    int distance;
};

// time complex: 인접리스트 ne, 인접행렬 n^3. dijkstra보다 느림. 
// n-1번 돌린 것과 n번 돌린것과 최단 거리가 다르다면 사이클 존재.
// 가중치 음수일때만 벨만포드 사용 권장
vector<int> bellman_ford(int n, int start, const vector<vector<Edge>>& graph) {
    vector<int> distances(n, INF);
    distances[start] = 0;

    for (int k = 1; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (const auto& edge: graph[u]) {
                distances[edge.to] = min(distances[edge.to], distances[u] + edge.distance);
            }
        }
    }

    return distances;
}


int main() {
    int n, e;
    cin >> n >> e;
    
    vector<vector<Edge>> graph(n);

    for (int i = 0; i < e; i++) {
        int v, u, weight;
        cin >> v >> u >> weight;

        graph[v].push_back({u, weight});
    }

    auto distances = bellman_ford(n, 0, graph);
    for (auto dis: distances) {
        cout << dis << " ";
    }
}