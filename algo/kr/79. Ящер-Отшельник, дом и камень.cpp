#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define int long long

int dp[610][610];

int32_t main() {
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> dp[i][j];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] += dp[i][j - 1];
    }
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    for (int j = i; j <= m; j++) {
      int sum = 0;
      for (int k = 1; k <= n; k++) {
        sum += dp[k][j] - dp[k][i - 1];
        ans = max(sum, ans);
        if (sum < 0)
          sum = 0;
      }
    }
  }

  cout << ans;

  return 0;
}