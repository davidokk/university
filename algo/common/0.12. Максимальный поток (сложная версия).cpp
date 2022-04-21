#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

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

  vector<vector<edge>> g;
  vector<int> level;
  vector<int> last;
};

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  Graph g(n);
  while (m--) {
    int l, r, w;
    cin >> l >> r >> w;
    g.add_edge(l - 1, r - 1, w);
  }

  cout << g.dinic(0, n - 1);

}