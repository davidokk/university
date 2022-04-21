#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;

  vector<set<int>> g(n);

  while (m--) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    g[x].insert(y);
    g[y].insert(x);
  }

  for (const auto& to : g) {
    cout << to.size() << " ";
    for (const auto& v : to)
      cout << v + 1 << " ";
    cout << "\n";
  }

}