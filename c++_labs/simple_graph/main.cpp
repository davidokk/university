#include <iostream>
#include <set>
#include <map>
#include <fstream>

using namespace std;

class Graph {
 public:
  bool AddVertex(const int v) {
    if (g.count(v))
      return false;
    g.insert({v, {}});
    return true;
  }

  bool AddEdge(const int l, const int r) {
    if (!g.count(l) || !g.count(r))
      return false;
    g[l].insert(r);
    g[r].insert(l);
    return true;
  }

  int countIsolatedVertices() const {
    int cnt {0};
    for (const auto[v, s] : g)
      if (s.empty())
        ++cnt;
    return cnt;
  }

 private:
  map<int, set<int>> g;
};

istream& operator>> (istream& is, Graph& G) {
  int n;
  is >> n;
  //cout << "enter " << n << " vertices: ";
  while (n--) {
    int x;
    is >> x;
    G.AddVertex(x);
  }

  int m;
  // cout << "enter number of edges: ";
  is >> m;
  // cout << "enter " << m << " edges: ";
  while (m--) {
    int x, y;
    is >> x >> y;
    if (!G.AddEdge(x, y)) {
      throw invalid_argument("");
      // cerr << "There isn't this vertex";
      //  return 1;
    }
  }
  return is;
}

int main() {

  Graph G;
  ifstream fin("input.txt");
  fin >> G;

  // int n, m;
  // cout << "enter number of vertices: ";
  // cin >> n;
  // cout << "enter " << n << " vertices: ";
  // while (n--) {
  //   int x;
  //   cin >> x;
  //   G.AddVertex(x);
  // }

  // cout << "enter number of edges: ";
  // cin >> m;
  // cout << "enter " << m << " edges: ";
  // while (m--) {
  //   int x, y;
  //   cin >> x >> y;
  //   if (!G.AddEdge(x, y)) {
  //     cerr << "There isn't this vertex";
  //     return 1;
  //   }
  // }

  cout << G.countIsolatedVertices();

  return 0;
}
