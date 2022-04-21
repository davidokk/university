#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

size_t lower_bound(const vector<int>& a, int val) {
  size_t l = 0, r = a.size();
  while (l < r) {
    size_t m = (l + r) / 2;
    if (a[m] < val)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

size_t upper_bound(const vector<int>& a, int val) {
  size_t l = 0, r = a.size();
  while (l < r) {
    size_t m = (l + r) / 2;
    if (a[m] <= val)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

bool binary_search(const vector<int>& a, int val) {
  auto pos = lower_bound(a, val);
  return pos < a.size() && a[pos] == val;
}

int main() {
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int n;
  cin >> n;
  vector<int> a(n);
  for (auto& i : a)
    cin >> i;
  int k;
  cin >> k;
  while (k--) {
    int num;
    cin >> num;
    cout << binary_search(a, num) << " "
         << lower_bound(a, num) << " "
         << upper_bound(a, num) << endl;
  }

}