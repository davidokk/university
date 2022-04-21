#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

using Node = vector<int>;

const int N = 1e5 + 10;
int a[N];
Node t[4 * N];

vector<int> merge(const Node& l, const Node& r) {
  vector<int> res;
  std::merge(l.begin(), l.end(), r.begin(), r.end(),back_inserter(res));
  if (res.size() > 4)
    return vector<int>{res[0], res[1], res[res.size() - 2], res[res.size() - 1]};
  else
    return res;
}

void build(int v, int tl, int tr) {
  if (tr - tl == 1) {
    t[v].push_back(a[tl]);
    return;
  }
  int m = (tl + tr) / 2;
  build(2 * v, tl, m);
  build(2 * v + 1, m, tr);
  t[v] = merge(t[2 * v], t[2 * v + 1]);
}

void set(int v, int tl, int tr, int idx, int val) {
  if (idx == tl && tr == idx + 1) {
    t[v] = vector<int>{val};
    return;
  }
  int m = (tl + tr) / 2;
  if (idx < m)
    set(2 * v, tl, m, idx, val);
  else
    set(2 * v + 1, m, tr, idx, val);
  t[v] = merge(t[2 * v], t[2 * v + 1]);
}

vector<int> find(int v, int tl, int tr, int l, int r) {
  if (tl == l && tr == r)
    return t[v];
  int m = (tl + tr) / 2;
  if (r <= m)
    return find(2 * v, tl, m, l, r);
  if (m <= l)
    return find(2 * v + 1, m, tr, l, r);
  return merge(
      find(2 * v, tl, m, l, m),
      find(2 * v + 1, m, tr, m, r)
  );
}

long long ans(const vector<int>& v) {
  vector<long long> p;
  for (int i = 0; i < v.size(); ++i)
    for (int j = 0; j < v.size(); ++j)
      if (i != j)
        p.push_back(1ll * v[i] * v[j]);
  return *max_element(p.begin(), p.end());
}

int main() {

  // ifstream cin("input.txt");
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    cin >> a[i];
  build(1, 0, n);

  while (m--) {
    char q;
    cin >> q;
    if (q == '?') {
      int l, r;
      cin >> l >> r;
      cout << ans(find(1, 0, n, l - 1, r)) << endl;
    } else {
      int idx, val;
      cin >> idx >> val;
      set(1, 0, n, idx - 1, val);
    }
  }

  return 0;
}