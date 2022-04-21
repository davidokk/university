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

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      if (x)
        p[j] = i + 1;
    }
  }

  for (auto& i : p)
    cout << i << " ";

}