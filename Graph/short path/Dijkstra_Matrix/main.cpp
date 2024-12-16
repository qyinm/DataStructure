#include <iostream>
#define inf 10000000
using namespace std;

int graph[5][5] = {
        {0, 6, inf, 1, inf},
        {6, 0, 5, 2, 2},
        {inf, 5, 0, inf, 5},
        {1, 2, inf, 0, 1},
        {inf, 2, 5, 1, 0}
};

int distance_data[5];
bool found[5];
int n = 5;
int choose_node() {
    int min_idx = 0;
    int Min = inf;
    for (int idx = 0; idx < n; ++idx) {
        if (found[idx] || Min <= distance_data[idx])
            continue;
        min_idx = idx;
        Min = distance_data[idx];
    }
    return min_idx;
}

int dijkstra(int start) {
    for (int i = 0; i < 5; ++i) {
        distance_data[i] = graph[start][i];
    }

    found[start] = true;
    for (int i = 0; i < n - 2; ++i) {
        int u = choose_node();
        found[u] = true;
        for (int w = 0; w < n; ++w) {
            if (found[w] || distance_data[u] + graph[u][w] >= distance_data[w])
                continue;
            distance_data[w] = distance_data[u] + graph[u][w];
        }
    }
}

int main() {
    dijkstra(0);

    for (const auto &dis: distance_data) {
        cout << dis << " ";
    }
    return 0;
}
