/*
노드수 엣지수
출발점 도착점
6 8
0 1
0 2
0 3
1 4
2 4
3 4
3 5
2 5
예상 결과
0 3 2 5 1 4
*/
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
  int count;
  vector<int> links;
} node;

void topSort(vector<node> graph, int n) {
  int i, j, k, top;
  node ptr;
  top = -1;
  for (i = 0; i < n; i++) {
    if (!graph[i].count) {
      // graph[i].count = top;
      top = i;
    }
  }

  for (i = 0; i < n; i++) {
    if (top == -1) {
      cerr << "\nNetwork has a cycle. Sort terminated. \n";
      exit(0);
    } else {
      j = top;
      top = graph[top].count;
      cout << j << " ";
      for (const auto &link : graph[j].links) {
        k = link;
        graph[k].count--;
        if (graph[k].count == 0) {
          graph[k].count = top;
          top = k;
        }
      }
    }
  }
}

int main() {
  int n, e;
  cin >> n >> e;
  vector<node> graph(n);

  for (int i = 0; i < e; i++) {
    int start, end;
    cin >> start >> end;
    graph[start].links.push_back(end);
    graph[end].count += 1;
  }

  topSort(graph, n);
}