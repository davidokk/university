#include <iostream>
#include <fstream>

using namespace std;

bool g[110][110];

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    g[x][y] = true;
    g[y][x] = true;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cout << g[i][j] << " ";
    cout << "\n";
  }
}