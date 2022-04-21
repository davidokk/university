#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;
  vector<int> p(n);

  while (--n) {
    int x, y;
    cin >> x >> y;
    p[y - 1] = x;
  }

  for (auto& i : p)
    cout << i << " ";

}