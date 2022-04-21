#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int dp[1010][1010];

int main() {

  ifstream cin("in.txt");
  ofstream cout("out.txt");

  int x, y, z;
  cin >> x >> y >> z;

  string s, t;
  cin >> s >> t;

  for (int i = 0; i <= s.size(); ++i)
    dp[i][0] = x * i;
  for (int i = 0; i <= t.size(); ++i)
    dp[0][i] = y * i;

  for (int i = 1; i <= s.size(); ++i) {
    for (int j = 1; j <= t.size(); ++j) {
      dp[i][j] = min({
        dp[i - 1][j] + x,
        dp[i][j - 1] + y,
        dp[i - 1][j - 1] + z * (s[i - 1] != t[j - 1])
      });
    }
  }

  cout << dp[s.size()][t.size()];

  return 0;
}