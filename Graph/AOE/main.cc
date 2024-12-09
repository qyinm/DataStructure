/*
9 11 0 8
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
earliest event time : 0 6 4 5 7 7 16 14 18 
latest event time : 0 6 6 8 7 10 16 14 18 
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Edge {
 public:
  int to;
  int cost;
  Edge(int to, int cost) : to(to), cost(cost) {};
};

class Node {
  public:
    int indegree = 0;
    vector<Edge> links;
};

vector<int> earlist_event_time(int start, int n, vector<Node> graph) {
  vector<int> eet(n, -INT_MAX);
  eet[start] = 0;
  
  int top = -1;
  for (int i = 0; i < n; i++) {
    if(graph[i].indegree == 0) {
      graph[i].indegree = top;
      top = i;
    }
  }

  int current_node;
  for (int i = 0; i < n; i++) {
    if (top == -1) {
      cout << "[ERROR] This network has cycle";
      return {};
    }
    current_node = top;
    top = graph[top].indegree;
    for (const auto& edge : graph[current_node].links) {
      graph[edge.to].indegree -= 1;
      eet[edge.to] = max(eet[edge.to], eet[current_node] + edge.cost);
      if (graph[edge.to].indegree == 0) {
        graph[edge.to].indegree = top;
        top = edge.to;
      }
    }
  }

  cout << "earliest event time : "; 
  for (const auto& time : eet) {
    cout << time << " ";
  }
  cout << endl;

  return eet;
}

vector<int> topology_sort(int start, int n, vector<Node> graph) {
  vector<int> topology;
  
  int top = -1;
  for (int i = 0; i < n; i++) {
    if(graph[i].indegree == 0) {
      graph[i].indegree = top;
      top = i;
    }
  }

  int current_node;
  for (int i = 0; i < n; i++) {
    if (top == -1) {
      cout << "[ERROR] This network has cycle";
      return {};
    }
    current_node = top;
    topology.push_back(current_node);
    top = graph[top].indegree;
    for (const auto& edge : graph[current_node].links) {
      graph[edge.to].indegree -= 1;
      if (graph[edge.to].indegree == 0) {
        graph[edge.to].indegree = top;
        top = edge.to;
      }
    }
  }

  return topology;
}



vector<int> latest_event_time(int eet_last, int n, vector<int> topology, vector<Node> graph) {
  vector<int> let(n, INT_MAX);
  let[topology[n - 1]] = eet_last;
  for (int i = n - 2; i >= 0; i--) {
    for (const auto& edge : graph[topology[i]].links) {
      let[topology[i]] = min(let[topology[i]], let[edge.to] - edge.cost);
    }
  }
  cout << "latest event time : "; 
  for (const auto& time : let) {
    cout << time << " ";
  }
  cout << endl;

  return let;
}


int main() {
  int n, e, start, end;
  cin >> n >> e >> start >> end;

  vector<Node> graph(n);
  for (int i = 0; i < e; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;

    graph[from].links.push_back({to, cost});
    graph[to].indegree += 1;
  }
  auto eet = earlist_event_time(start, n, graph);
  auto topology = topology_sort(start, n, graph);
  auto let = latest_event_time(eet[n - 1], n, topology, graph);
}