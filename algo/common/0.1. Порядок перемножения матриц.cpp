#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int dp[110][110];

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;

  vector<pair<int, int>> m(n);
  for (auto& p : m)
    cin >> p.first >> p.second;

  for (int l = 2; l <= n; ++l) {
    for (int i = 0; i < n - l + 1; ++i) {
      int k = i + l - 1;
      dp[i][k] = 2e9;
      for (int j = i; j < i + l; ++j) {
        dp[i][k] = min(dp[i][k], dp[i][j] + dp[j + 1][k] + m[i].first * m[j].second * m[k].second);
      }
    }
  }

  cout << dp[0][n - 1];

  return 0;
}