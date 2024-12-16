#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// DFS 함수
void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& recStack, stack<int>& topoStack, bool hasCycle) {
    visited[node] = true;
    recStack[node] = true; // 현재 노드를 재귀 스택에 추가

    // 인접 노드를 탐색
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, recStack, topoStack, hasCycle);
        } else if (recStack[neighbor]) {
            hasCycle = true; // 사이클 발견
        }
    }

    recStack[node] = false; // 현재 노드를 재귀 스택에서 제거
    topoStack.push(node); // 모든 인접 노드를 처리한 후 스택에 추가
}

// 사이클 체크 함수
bool hasCycleInGraph(const vector<vector<int>>& graph, int n) {
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false); // 재귀 스택을 추적
    bool hasCycle = false;

    // 모든 노드에 대해 DFS 수행
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited, recStack, stack<int>(), hasCycle);
        }
    }

    return hasCycle;
}

// 위상 정렬 함수
vector<int> topologicalSort(const vector<vector<int>>& graph, int n) {
    vector<bool> visited(n, false);
    stack<int> topoStack;
    vector<int> result;

    // 모든 노드에 대해 DFS 수행
    vector<bool> recStack(n, false); // 재귀 스택 초기화
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited, recStack, topoStack, false);
        }
    }

    // 스택에서 노드를 꺼내며 정렬된 순서를 저장
    while (!topoStack.empty()) {
        result.push_back(topoStack.top());
        topoStack.pop();
    }

    return result;
}

int main() {
    // 입력: 정점 개수와 간선
    int n, e;
    cin >> n >> e;

    vector<vector<int>> graph(n);

    // 그래프 입력
    for (int i = 0; i < e; ++i) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }

    // 사이클 체크
    if (hasCycleInGraph(graph, n)) {
        cout << "[ERROR] The graph has a cycle." << endl;
        return 1; // 사이클이 존재하면 프로그램 종료
    }

    // 위상 정렬 수행
    vector<int> topoOrder = topologicalSort(graph, n);

    // 결과 출력
    cout << "Topological Sort Order: ";
    for (int node : topoOrder) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}