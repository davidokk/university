#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> p, s;
int cnt;

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

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;

  cnt = n;
  p.resize(n + 1);
  iota(p.begin(), p.end(), 0);
  s.resize(n + 1);
  fill(s.begin(), s.end(), 1);

  while (m--) {
    int a, b;
    cin >> a >> b;
    merge(a, b);
    cout << cnt << endl;
  }

}