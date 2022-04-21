#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Graph {
  struct edge {
    int to;
    int capacity;
    int flow;
    size_t back;
  };

  explicit Graph(int n) : g(n), level(n), last(n) {}

  void add_edge(int from, int to, int capacity) {
    edge e1{.to = to, .capacity = capacity, .flow = 0, .back = g[to].size()};
    edge e2{.to = from, .capacity = 0, .flow = 0, .back = g[from].size()};
    g[from].push_back(e1);
    g[to].push_back(e2);
  }

  void bfs(int s) {
    queue<int> q;
    q.push(s);
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (const auto& edge : g[v]) {
        if (level[edge.to] == -1 && edge.flow < edge.capacity) {
          q.push(edge.to);
          level[edge.to] = level[v] + 1;
        }
      }
    }
  }

  int dfs(int v, int t, int flow) {
    if (flow == 0 || v == t)
      return flow;
    for (int& i = last[v]; i < g[v].size(); ++i) {
      auto& edge = g[v][i];
      if (level[edge.to] == level[v] + 1) {
        int min_flow = dfs(edge.to, t, min(flow, edge.capacity - edge.flow));
        if (min_flow != 0) {
          auto& back_edge = g[edge.to][edge.back];
          edge.flow += min_flow;
          back_edge.flow -= min_flow;
          return min_flow;
        }
      }
    }
    return 0;
  }

  long long dinic(int s, int t) {
    long long ans = 0;
    while (true) {
      bfs(s);
      if (level[t] == -1)
        break;
      fill(last.begin(), last.end(), 0);
      while (int flow = dfs(s, t, 1e9))
        ans += flow;
    }
    return ans;
  }

  vector<pair<int, int>> restore(int s, int to) {
    queue<int> q;
    q.push(s);
    vector<int> used(g.size());
    used[s] = true;
    vector<pair<int, int>> res;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto& edge : g[v]) {
        if (edge.flow == 1 && v <= to && edge.to && edge.to <= to)
          res.emplace_back(v, edge.to);
        if (!used[edge.to]) {
          used[edge.to] = true;
          q.push(edge.to);
        }
      }
    }
    return res;
  }

  vector<vector<edge>> g;
  vector<int> level;
  vector<int> last;
};

int n, m;

pair<int, int> diag_num(int i, int j) {
  return make_pair(i + j, i - j + 3 * n - 2);
}

pair<int, int> index_by_diag(int f, int s) {
  int i = (f + s - 3 * n + 2) / 2;
  int j = f - i;
  return make_pair(i, j);
}

vector<pair<int, int>> put_pluses(const vector<pair<int, int>>& v) {
  int diags_count = 4 * n - 2;
  int s = diags_count;
  int t = s + 1;
  Graph g(2 + diags_count);
  vector<bool> blocked(diags_count);
  for (const auto& [i, j] : v) {
    auto diag = diag_num(i, j);
    blocked[diag.first] = true;
    blocked[diag.second] = true;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      auto diag = diag_num(i, j);
      g.add_edge(diag.first, diag.second, 1);
    }
  }
  for (int i = 0; i < diags_count; ++i) {
    if (!blocked[i]) {
      if (i < diags_count / 2)
        g.add_edge(s, i, 1);
      else
        g.add_edge(i, t, 1);
    }
  }
  g.dinic(s, t);
  vector<pair<int, int>> res = g.restore(s, diags_count - 1);
  for (auto& [l, r] : res) {
    auto idx = index_by_diag(l, r);
    l = idx.first;
    r = idx.second;
  }
  return res;
}

vector<pair<int, int>> put_crosses(const vector<pair<int, int>>& v) {
  vector<bool> blocked_i(n), blocked_j(n);
  for (const auto& [i, j] : v) {
    blocked_i[i] = true;
    blocked_j[j] = true;
  }
  vector<pair<int, int>> res;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!blocked_i[i] && !blocked_j[j]) {
        res.emplace_back(i, j);
        blocked_i[i] = blocked_j[j] = true;
      }
    }
  }
  return res;
}

int main() {

  ifstream cin("fashion.in");
  ofstream cout("fashion.out");

  cin >> n >> m;
  vector<pair<int, int>> pluses;
  vector<pair<int, int>> crosses;
  vector<vector<char>> t(n, vector<char>(n, ' '));
  int sum = 0;

  while (m--) {
    char c;
    int i, j;
    cin >> c >> i >> j;
    --i; --j;
    t[i][j] = c;
    if (c != '+') {
      crosses.emplace_back(i, j);
      ++sum;
    }
    if (c != 'x') {
      pluses.emplace_back(i, j);
      ++sum;
    }
  }

  auto t1 = t;
  for (auto [i, j] : put_pluses(pluses)) {
    t1[i][j] = (t1[i][j] == 'x' ? 'o' : '+');
    ++sum;
  }
  for (auto [i, j] : put_crosses(crosses)) {
    t1[i][j] = (t1[i][j] == '+' ? 'o' : 'x');
    ++sum;
  }

  int k = 0;
  vector<string> ans;
  ostringstream ss;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (t[i][j] != t1[i][j]) {
        ss << t1[i][j] << " " << i + 1 << " " << j + 1 << "\n";
        ++k;
      }
    }
  }

  cout << sum << " " << k << "\n" << ss.str();

}