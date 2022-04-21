#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;

  vector<set<int>> g(n);
  vector<int> m(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      if (x)
        g[i].insert(j);
    }
  }

  queue<int> q;
  int cnt = 0;
  while (cnt != n) {
    int i = 0;
    while (m[i++] != 0);
    m[i - 1] = ++cnt;
    q.push(i - 1);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto& to: g[v]) {
        if (m[to] == 0) {
          m[to] = ++cnt;
          q.push(to);
        }
      }
    }
  }

  for (auto& i : m)
    cout << i << " ";

}