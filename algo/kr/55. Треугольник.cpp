#include <iostream>
#include <fstream>

using namespace std;

int dp[1010][1010];

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i + 1; j++)
      cin >> dp[i][j];
  }

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i + 1; j++)
      if (j == 0)
        dp[i][j] += dp[i - 1][j];
      else if (j == i)
        dp[i][j] += dp[i - 1][j - 1];
      else
        dp[i][j] += max(dp[i - 1][j], dp[i - 1][j - 1]);
  }

  int mx = -1;
  for (int i = 0; i < n; i++)
    mx = max(mx, dp[n - 1][i]);

  cout << mx;

  return 0;
}