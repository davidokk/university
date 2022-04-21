#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int dp[7010][7010];
int p[7010][7010];

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  string s;
  cin >> s;
  size_t n = s.size();
  for (int i = 0; i < n; ++i)
    dp[i][i] = 1;

  for (int k = 1; k < n; ++k) {
    int i = 0, j = k;
    while (j < n) {
      if (s[i] == s[j]) {
        dp[i][j] = dp[i + 1][j - 1] + 2;
        p[i][j] = 1;
      } else {
        if (dp[i + 1][j] > dp[i][j - 1]) {
          dp[i][j] = dp[i + 1][j];
          p[i][j] = 2;
        } else {
          dp[i][j] = dp[i][j - 1];
          p[i][j] = 3;
        }
      }
      ++i;
      ++j;
    }
  }

  cout << dp[0][n - 1] << endl;

  string t;
  size_t i = 0, j = n - 1;
  while (p[i][j] != 0) {
    if (p[i][j] == 1) {
      t += s[i];
      ++i;
      --j;
    } else if (p[i][j] == 2) {
      ++i;
    } else {
      --j;
    }
  }

  string w(t.rbegin(), t.rend());

  if (i == j)
    cout << t + s[i] + w;
  else
    cout << t + w;

  return 0;
}