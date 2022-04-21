#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Node {
  long long sum;
  int l;
  int r;
  Node* left = nullptr;
  Node* right = nullptr;
};

Node* build(int l, int r, const vector<int>& a) {
  if (l == r)
    return new Node{a[l], l, l};
  int m = (l + r) / 2;
  Node* v = new Node{};
  v->left = build(l, m, a);
  v->right = build(m + 1, r, a);
  v->sum = v->left->sum + v->right->sum;
  v->l = l;
  v->r = r;
  return v;
}

long long sum(Node* v, int l, int r) {
  if (v->l == l && r == v->r)
    return v->sum;
  if (r < v->l || l > v->r)
    return 0;
  return sum(v->left, l, min(r, v->left->r)) + sum(v->right, max(l, v->right->l), r);
}

void add(Node* v, int i, int x) {
  if (v->l == i && v->r == i) {
    v->sum += x;
    return;
  }
  if (i <= v->left->r)
    add(v->left, i, x);
  else
    add(v->right, i, x);
  v->sum += x;
}

void remove(Node* v) {
  if (v) {
    remove(v->left);
    remove(v->right);
    delete v;
  }
}

int main() {

  //ifstream cin("input.txt");
  //ofstream cout("output.txt");
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (auto& i : a)
    cin >> i;

  Node* root = build(0, a.size() - 1, a);

  int q;
  cin >> q;
  while (q--) {
    string s;
    int x, y;
    cin >> s >> x >> y;
    if (s == "FindSum")
      cout << sum(root, x, y - 1) << endl;
    else
      add(root, x, y);
  }

  remove(root);
  return 0;
}