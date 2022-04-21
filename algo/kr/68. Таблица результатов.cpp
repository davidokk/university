#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
  int l, r, q;
  cin >> l >> r >> q;

  unordered_map<string, int> points;
  set<pair<int, string>> teams;

  while (q--) {
    string s;
    cin >> s;
    if (s == "show") {
      int n = max(0, (int)teams.size() - l + 1);
      cout << n << "\n";
      vector<string_view> v(n);
      auto it = teams.begin();
      for (int i = 0; i < n; ++i)
        v[i] = (it++)->second;
      for (auto it = rbegin(v); it != rend(v); ++it)
        cout << *it << "\n";
    } else {
      int t, b;
      cin >> t >> b;
      if (points.find(s) != points.end())
        teams.erase(make_pair(points[s], s));
      points[s] = t * 100000 - b;
      teams.emplace(points[s], s);
      if (teams.size() > r)
        teams.erase(teams.begin());
    }
  }
}