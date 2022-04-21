#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

void insert(set<pair<int, int>>& s, int to, int w) {
  auto it = s.upper_bound(make_pair(to, -1));
  if (it != s.end() && it->first == to) {
    if (it->second > w) {
      s.erase(it);
      s.emplace(to, w);
    }
  } else {
    s.emplace(to, w);
  }
}

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;

  vector<set<pair<int, int>>> g(n);

  while (m--) {
    int x, y, w;
    cin >> x >> y >> w;
    insert(g[x - 1], y - 1, w);
    insert(g[y - 1], x - 1, w);
  }

  vector<long long> d(n, 1e18);
  set<pair<int, int>> q;

  d[0] = 0;
  q.emplace(0, 0);
  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());
    for (auto& [to, w] : g[v]) {
      if (d[v] + w < d[to]) {
        q.erase(make_pair(d[to], to));
        d[to] = d[v] + w;
        q.emplace(d[to], to);
      }
    }
  }

  cout << d[n - 1];

}