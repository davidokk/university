#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

struct DSU {
  vector<int> p, s;
  int cnt;

  explicit DSU(int n) : cnt(n), p(n + 1), s(n + 1, 1) {
    iota(p.begin(), p.end(), 0);
  }

  int parent(int v) {
    if (v == p[v])
      return v;
    return p[v] = parent(p[v]);
  }

  void merge(int l, int r) {
    int lp = parent(l);
    int rp = parent(r);
    if (lp == rp)
      return;
    if (s[lp] > s[rp]) {
      swap(lp, rp);
      swap(l, r);
    }
    --cnt;
    p[lp] = rp;
    s[rp] += s[lp];
  }

  int count() { return cnt; }

};

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, m, k;
  cin >> n >> m >> k;

  DSU dsu(n);
  vector<pair<pair<int, int>, bool>> g;

  while (m--) {
    int a, b;
    cin >> a >> b;
    g.emplace_back(make_pair(a, b), true);
  }

  vector<int> z(k);
  for (auto& i : z) {
    cin >> i;
    g[i - 1].second = false;
  }

  for (const auto&[road, b] : g) {
    if (b)
      dsu.merge(road.first, road.second);
  }

  int cnt = dsu.count() != 1;
  for (int i = k - 1; i >= 0; --i) {
    auto road = g[z[i] - 1].first;
    dsu.merge(road.first, road.second);
    if (dsu.count() != 1)
      ++cnt;
    else
      break;
  }

  for (int i = 0; i < k - cnt; ++i)
    cout << 1;
  while (cnt--)
    cout << 0;
}