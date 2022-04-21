#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Node {
  int l;
  int r;
  long long sum = 0;
  long long max = 0;
  long long min = 0;
  long long add = 0;
  Node* left = nullptr;
  Node* right = nullptr;
};

Node* build(int l, int r) {
  if (l == r)
    return new Node{l, l};
  int m = (l + r) / 2;
  Node* v = new Node{};
  v->left = build(l, m);
  v->right = build(m + 1, r);
  v->l = l;
  v->r = r;
  return v;
}

void push(Node* v) {
  if (v->left) {
    v->left->add += v->add;
    v->right->add += v->add;
  }
  v->sum += v->add * (v->r - v->l + 1);
  v->max += v->add;
  v->min += v->add;
  v->add = 0;
}

long long sum(Node* v, int l, int r) {
  push(v);
  if (l > r)
    return 0;
  if (v->l == l && r == v->r)
    return v->sum;
  return sum(v->left, l, min(r, v->left->r)) + sum(v->right, max(l, v->right->l), r);
}

const long long INF = 1e18;

long long min(Node* v, int l, int r) {
  push(v);
  if (l > r)
    return INF;
  if (v->l == l && r == v->r)
    return v->min;
  return min(min(v->left, l, min(r, v->left->r)), min(v->right, max(l, v->right->l), r));
}

long long max(Node* v, int l, int r) {
  push(v);
  if (l > r)
    return -INF;
  if (v->l == l && r == v->r)
    return v->max;
  return max(max(v->left, l, min(r, v->left->r)), max(v->right, max(l, v->right->l), r));
}

void update(Node* v, int i, int x) {
  push(v);
  if (i < v->l || i > v->r)
    return;
  if (v->l == v->r) {
    v->sum = x;
    v->max = x;
    v->min = x;
    return;
  }
  update(v->left, i, x);
  update(v->right, i, x);
  v->sum = v->left->sum + v->right->sum;
  v->max = max(v->left->max, v->right->max);
  v->min = min(v->left->min, v->right->min);
}

void add(Node* v, int l, int r, int x) {
  push(v);
  if (r < v->l || l > v->r)
    return;
  if (v->l == l && v->r == r) {
    v->add += x;
    push(v);
    return;
  }
  add(v->left, l, min(r, v->left->r), x);
  add(v->right, max(l, v->right->l), r, x);
  v->sum = v->left->sum + v->right->sum;
  v->max = max(v->left->max, v->right->max);
  v->min = min(v->left->min, v->right->min);
}

void print(Node* v) {
  if (v) {
    cout << "(" << v->add << " " << v->sum << ") ";
    print(v->left);
    print(v->right);
  }
}

void remove(Node* v) {
  if (v) {
    remove(v->left);
    remove(v->right);
    delete v;
  }
}

int main() {

  ifstream cin("input.txt");
  ofstream cout("output.txt");

  int n;
  cin >> n;

  Node* root = build(0, n - 1);

  while (true) {
    int t, a, b, v, i;
    cin >> t;
    switch (t) {
      case 1:
        cin >> i >> v;
        update(root, i, v);
        break;
      case 2:
        cin >> a >> b >> v;
        add(root, a, b, v);
        break;
      case 3:
        cin >> a >> b;
        cout << sum(root, a, b) << endl;
        break;
      case 4:
        cin >> a >> b;
        cout << min(root, a, b) << endl;
        break;
      case 5:
        cin >> a >> b;
        cout << max(root, a, b) << endl;
        break;
      default:
        remove(root);
        return 0;
    }
  }

}