#include <iostream>
#include <fstream>

using namespace std;

int dp[700][700];
int p[700][700];
string s;

bool check(int l, int r, int d) {
  if ((r - l + 1) % d != 0)
    return false;
  for (int i = l + d; i <= r; i += d) {
    for (int j = 0; j < d; ++j)
      if (s[l + j] != s[i + j])
        return false;
  }
  return true;
}

int fold(int l, int r) {
  int ans = 1e9;
  for (int d = 1; d <= (r - l + 1) >> 1; ++d)
    if (check(l, r, d)) {
      int cnt = (r - l + 1) / d;
      int len = (int)to_string(cnt).size() + 2 + dp[l][l + d - 1];
      if (ans > len) {
        ans = len;
        p[l][r] = -d;
      }
    }
  return ans;
}

string answer(int l, int r) {
  if (l == r)
    return string(1, s[l]);
  if (p[l][r] < 0)
    return to_string((r - l + 1) / -p[l][r]) + "(" + answer(l, l - p[l][r] - 1) + ")";
  return answer(l, p[l][r]) + answer(p[l][r] + 1, r);
}

int main() {
  ifstream cin("folding.in");
  ofstream cout("folding.out");

  cin >> s;
  int n = (int)s.size();

  for (int i = 0; i < n; ++i)
    dp[i][i] = 1;

  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i < n - len + 1; ++i) {
      int j = i + len - 1;
      dp[i][j] = fold(i, j);
      for (int k = i; k < j; ++k) {
        if (dp[i][j] > dp[i][k] + dp[k + 1][j]) {
          dp[i][j] = dp[i][k] + dp[k + 1][j];
          p[i][j] = k;
        }
      }
    }
  }

  cout << answer(0, n - 1);
}