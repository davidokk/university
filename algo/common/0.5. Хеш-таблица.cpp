#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int m, c, n;
  cin >> m >> c >> n;

  vector<int> v(m, -1);
  while (n--) {
    int x;
    cin >> x;
    int h = x % m, i = 0;
    while (v[h] != -1 && v[h] != x)
      h = ((x % m) + c * ++i) % m;
    v[h] = x;
  }

  for (auto& i : v)
    cout << i << " ";

  return 0;
}