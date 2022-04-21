#include <iostream>

using namespace std;

int dp[1010][1010];

int main() {

  int n, k;
  cin >> n >> k;
  for (int i = 0; i <= n; ++i)
    dp[i][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      dp[i][j] %= (int) 1e9 + 7;
    }
  }
  cout << dp[n][k];

  return 0;
}