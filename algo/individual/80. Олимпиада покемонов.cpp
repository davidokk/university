#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int dp[2000][3000];

int main() {
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int n, m;
  cin >> n >> m;
  vector<int> p(n), b(m);
  for (auto& i : p)
    cin >> i;
  for (auto& i : b)
    cin >> i;

  for (int i = 1; i < m; ++i) {
    dp[0][i] = dp[0][i - 1];
    if (b[i] < b[dp[0][i]])
      dp[0][i] = i;
  }

  int INF = 1e9;
  for (int i = 1; i < n; ++i) {
    dp[i][i - 1] = INF;
    for (int j = i; j < m; j++) {
      dp[i][j] = dp[i][j - 1];
      if (dp[i - 1][j - 1] == INF)
        continue;
      int l = p[i - 1] + b[dp[i - 1][j - 1]];
      int r = p[i] + b[j];
      if (l < r) {
        int l1 = dp[i][j] == INF ? INF : p[i] + b[dp[i][j]];
        if (r < l1)
          dp[i][j] = j;
      }
    }
  }

  if (dp[n - 1][m - 1] == INF) {
    cout << -1;
  } else {
    vector<int> ans;
    int i = n - 1, j = m - 1;
    while (i >= 0) {
      ans.push_back(dp[i][j] + 1);
      j = dp[i][j] - 1;
      --i;
    }
    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
      cout << *it << " ";
  }

}