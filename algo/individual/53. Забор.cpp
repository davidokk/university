#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

struct Segment {
  int pref = 1;
  int suf = 1;
  bool painted_pref = false;
  bool painted_suf = false;
  int ans[2] = {1, 0};
  int len = 1;
};

const int N = 1048576;
Segment t[2 * N];

bool full(const Segment& s, bool painted) {
  return !(painted ^ s.painted_pref) && s.pref == s.len;
}

Segment merge(const Segment& l, const Segment& r) {
  Segment res;
  res.ans[0] = max(l.ans[0], r.ans[0]);
  res.ans[1] = max(l.ans[1], r.ans[1]);
  res.painted_pref = l.painted_pref;
  res.painted_suf = r.painted_suf;
  res.pref = l.pref;
  res.suf = r.suf;
  res.len = l.len + r.len;

  if (!(l.painted_suf ^ r.painted_pref))
    res.ans[l.painted_suf] = max(res.ans[l.painted_suf], l.suf + r.pref);

  if (full(l, r.painted_pref))
    res.pref += r.pref;
  if (full(r, l.painted_suf))
    res.suf += l.suf;

  return res;
}

void paint(Segment& s) {
  s.painted_pref = true;
  s.painted_suf = true;
  s.pref = s.suf = s.len;
  s.ans[0] = 0;
  s.ans[1] = s.len;
}

void build(int v, int tl, int tr) {
  if (tr - tl == 1) {
    t[v] = Segment{};
    return;
  }
  int m = (tl + tr) / 2;
  build(2 * v, tl, m);
  build(2 * v + 1, m, tr);
  t[v] = merge(t[2 * v], t[2 * v + 1]);
}

void paint(int v, int tl, int tr, int l, int r) {
  if (full(t[v], true))
    return;
  if (tl == l && tr == r) {
    paint(t[v]);
    return;
  }
  if (l >= r)
    return;
  int m = (tl + tr) / 2;
  paint(2 * v, tl, m, l, min(r, m));
  paint(2 * v + 1, m, tr, max(l, m), r);
  t[v] = merge(t[2 * v], t[2 * v + 1]);
}

Segment walk(int v, int tl, int tr, int l, int r) {
  if (full(t[v], true) || full(t[v], false)) {
    Segment s = t[v];
    s.len = r - l;
    s.pref = s.suf = s.len;
    s.ans[s.painted_pref] = s.len;
    s.ans[!s.painted_pref] = 0;
    return s;
  }
  if (tl == l && tr == r)
    return t[v];
  int m = (tl + tr) / 2;
  if (r <= m)
    return walk(2 * v, tl, m, l, r);
  if (m <= l)
    return walk(2 * v + 1, m, tr, l, r);
  return merge(
      walk(2 * v, tl, m, l, m),
      walk(2 * v + 1, m, tr, m, r)
  );
}

int main() {

  ifstream cin("fence.in");
  ofstream cout("fence.out");

  build(1, 0, N);

  char q;
  while (cin >> q) {
    if (q == 'F')
      break;
    int l, r;
    cin >> l >> r;
    assert(l <= r);
    if (q == 'L') {
      paint(1, 0, N, l - 1, r);
    } else {
      auto p = walk(1, 0, N, l - 1, r);
      cout << p.ans[0] << " " << p.ans[1] << "\n";
    }
  }

  return 0;
}