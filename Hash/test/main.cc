#include <iostream>
#include <map>

using namespace std;

struct vertex {
  vector<vertex*> alist;
  string name;
  vertex(string s) : name(s) {}
};

int main() {
  map<string, vertex*> m;

  string nameX = "x";
  string nameA = "a";
  vertex *x;
  x = new vertex(nameX);
  vertex *a;
  a = new vertex(nameA);
  m[nameX] = x;
  m[nameA] = a;

  vertex *f = m.find(nameA)->second;
  vertex *t = m.find(nameX)->second;

  f->alist.push_back(t);
  t->alist.push_back(f);

  vector<vertex*> visited;
  visited.push_back(f);

  for (auto v : visited) {
    if (v->name == nameA) {
      cout << v->name << endl;
      for (auto conn : v->alist) {
        cout << conn->name << " ";
      }
    }
  }
  cout << endl;

  cout << m.size();
  cout << m.begin()->first;
}