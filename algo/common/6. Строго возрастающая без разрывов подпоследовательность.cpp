#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;
  vector<int> a(n);
  for (auto& i : a)
    cin >> i;

  vector<int> dp(1, -2e9);

  for (auto i : a) {
    auto it = lower_bound(dp.begin(), dp.end(), i);
    if (it == dp.end())
      dp.push_back(i);
    else
      *it = min(*it, i);
  }

  cout << dp.size() - 1;

  return 0;
}