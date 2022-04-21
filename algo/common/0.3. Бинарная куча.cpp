#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;

  vector<int> a(n);
  for (auto& e : a)
    cin >> e;

  for (int i = n - 1; i > 0; --i) {
    if (a[i] < a[(i - 1) >> 1]) {
      cout << "No";
      return 0;
    }
  }

  cout << "Yes";

}