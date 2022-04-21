#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

int dp[310][310];

int32_t main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, k;
  cin >> n >> k;

  vector<int> a(k);
  for (auto& i : a)
    cin >> i;

  a.push_back(0);
  sort(a.begin(), a.end());
  a.push_back(n + 1);

  // dp[i][j] стоимость поддерева с узлами a[i]..a[j]
  // в диапазоне от a[i - 1] + 1 до a[j + 1] - 1

  for (int i = 1; i <= k; ++i)
    dp[i][i] = a[i + 1] - a[i - 1] - 1;

  for (int len = 1; len < k; ++len) {
    for (int i = 1; i + len <= k; ++i) {
      int j = i + len;
      dp[i][j] = 1e18;
      for (int root = i; root <= j; ++root)
        dp[i][j] = min(dp[i][j], dp[i][root - 1] + dp[root + 1][j]);
      dp[i][j] += a[j + 1] - a[i - 1] - 1;
    }
  }

  // for (int i = 1; i <= k; ++i) {
  //   for (int j = 1; j <= k; j++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  cout << dp[1][k];

  return 0;
}