#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

vector<set<int>> g;
vector<int> m;
int cnt = 0;

void dfs(int v) {
  for (auto& to : g[v])
    if (m[to] == 0) {
      m[to] = ++cnt;
      dfs(to);
    }
}

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;
  g.resize(n);
  m.resize(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      if (x)
        g[i].insert(j);
    }
  }

  while (cnt != n) {
    int i = 0;
    while (m[i++] != 0);
    m[i - 1] = ++cnt;
    dfs(i - 1);
  }

  for (auto& i : m)
    cout << i << " ";

}