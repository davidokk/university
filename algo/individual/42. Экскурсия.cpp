#include <iostream>
#include <fstream>
#include <queue>
#include <array>

using namespace std;

const int N = 31;
int INF = 1e9;

int d[N], p[N];
pair<int, int> pred[N];

struct edge {
  int w = INF, f = 0, u;
};

array<edge, 2> g[N][N];

void dijkstra(int l) {
  priority_queue<pair<int, int>> q;
  fill(d, d + N, INF);
  d[l] = 0;
  q.push(make_pair(0, l));
  while (!q.empty()) {
    auto [dist, v] = q.top();
    q.pop();
    if (dist > d[v])
      break;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < 2; j++) {
        if (g[v][i][j].w != INF && g[v][i][j].f < g[v][i][j].u) {
          int w = p[v] + g[v][i][j].w - p[i];
          if (d[i] > d[v] + w) {
            d[i] = d[v] + w;
            pred[i] = make_pair(v, j);
            q.push(make_pair(d[i], i));
          }
        }
      }
    }
  }
  for (int i = 0; i < N; ++i)
    p[i] = d[i];
}

void ford_bellman(int s, int n) {
  fill(d, d + N, INF);
  d[s] = 0;
  for (int k = 0; k < n; k++)
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        for (int q = 0; q < 2; q++) {
          auto& e = g[i][j][q];
          // if (e.w != INF) cout << e.u - e.f << endl;
          if (e.w != INF && e.f < e.u && d[j] > d[i] + e.w) {
            d[j] = d[i] + e.w;
            pred[j] = make_pair(i, q);
          }
        }
}

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n, s, t;
  cin >> n >> s >> t;

  int l, r, f, w;
  while (cin >> l >> r >> f >> w) {
    g[l][r][0] = {.w = w, .u = f};
    g[l][r][1] = {.w = -w, .u = 0};
    g[r][l] = g[l][r];
  }

  int flow = 0, cost = 0;
  while (flow < INF) {
    // dijkstra(s);
    ford_bellman(s, n);
    if (d[t] == INF)
      break;
    int delta = INF - flow;
    int v = t;
    while (v != s) {
      auto& e = g[pred[v].first][v][pred[v].second];
      delta = min(delta, e.u - e.f);
      v = pred[v].first;
    }
    v = t;
    while (v != s) {
      int pr = pred[v].first, j = pred[v].second;
      g[pr][v][j].f += delta;
      g[v][pr][1 - j].f -= delta;
      cost += g[pr][v][j].w * delta;
      v = pr;
    }
    flow += delta;
  }

  cout << flow << endl << cost;

}