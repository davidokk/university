#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;

  vector<int> a(m, 1);

  int mod = 1e9 + 7;

  for (int j = 0; j < n - 1; j++) {
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
      if (i != 0)
        b[i] = b[i - 1] + a[i];
      else
        b[i] = a[i];
      b[i] %= mod;
    }
    a = move(b);
  }

  cout << a[m - 1];

  return 0;
}