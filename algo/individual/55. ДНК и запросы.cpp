#include <fstream>
#include <map>
#include <cassert>
#include <random>
#include <iostream>

// #include "test.h"

using namespace std;

const map<char, short> M {
    {'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}
};

struct Node;
using NodePtr = Node*;

minstd_rand GEN;

struct Node {
  char value;
  size_t treap_number;
  size_t version = 0;
  int priority;
  size_t magic_number = -1;
  array<int, 4> sum;
  int size = 1;
  NodePtr left = nullptr, right = nullptr;

  Node(char v, size_t num) : treap_number(num), value(v), priority(GEN()) {
    fill(sum.begin(), sum.end(), 0);
    ++sum[M.at(value)];
  }
};

int copy_count = 0;

int size(NodePtr v) { return v ? v->size : 0; }
int count(NodePtr v, int i) { return v ? v->sum[i] : 0; }
NodePtr copy(NodePtr v) { ++copy_count; return new Node(*v); }

void push(NodePtr v) {
  if (v->left && (v->left->treap_number != v->treap_number || v->left->version != v->version)) {
    // if (v->left->treap_number != v->magic_number) {
      // cout << v->left->treap_number << "->" << v->treap_number << endl;
      v->left = copy(v->left);
    // }
    // v->left = copy(v->left);
    v->left->treap_number = v->treap_number;
    v->left->version = v->version;
    v->left->magic_number = v->magic_number;
  }
  if (v->right && (v->right->treap_number != v->treap_number || v->right->version != v->version)) {
    // if (v->right->treap_number != v->magic_number) {
    //   cout << v->right->treap_number << "->" << v->treap_number << endl;
      v->right = copy(v->right);
    // }
    // v->right = copy(v->right);
    v->right->treap_number = v->treap_number;
    v->right->version = v->version;
    v->right->magic_number = v->magic_number;
  }
}

void update(NodePtr v) {
  v->size = size(v->left) + size(v->right) + 1;
  for (int i = 0; i < 4; ++i)
    v->sum[i] = count(v->left, i) + count(v->right, i);
  ++v->sum[M.at(v->value)];
}

NodePtr merge(NodePtr a, NodePtr b) {
  if (!a) return b;
  if (!b) return a;
  // a = copy(a);
  // b = copy(b);
  push(a);
  push(b);
  if (GEN() % (size(a) + size(b)) < size(a)) {
  // if (a->priority > b->priority) {
    a->right = merge(a->right, b);
    update(a);
    return a;
  } else {
    b->left = merge(a, b->left);
    update(b);
    return b;
  }
}

pair<NodePtr, NodePtr> split(NodePtr a, int index) {
  if (!a) return {nullptr, nullptr};
  // a = copy(a);
  push(a);
  if (size(a->left) < index) {
    auto [l, r] = split(a->right, index - size(a->left) - 1);
    a->right = l;
    update(a);
    return {a, r};
  } else {
    auto [l, r] = split(a->left, index);
    a->left = r;
    update(a);
    return {l, a};
  }
}

pair<NodePtr, NodePtr> cut_swap(NodePtr a, NodePtr b, int j1, int j2, size_t num1, size_t num2) {
  NodePtr c = nullptr, d = nullptr;
  if (a) {
    c = copy(a);
    c->treap_number = num1;
  }
  if (b) {
    d = copy(b);
    d->treap_number = num2;
  }
  auto [first_left, first_right] = split(c, j1);
  auto [second_left, second_right] = split(d, j2);
  // if (second_right) {
  //   second_right->magic_number = num2;
    // second_right->treap_number = num1;
  // }
  // if (first_right) {
  //   first_right->magic_number = num1;
    // first_right->treap_number = num2;
  // }
  // copy_count = 0;
  auto l = merge(first_left, second_right);
  auto r = merge(second_left, first_right);
  // cout << copy_count << endl;
  return {l, r};
  // return {
  //   merge(first_left, second_right),
  //   merge(second_left, first_right)
  // };
}

array<int, 4> sum(NodePtr& v, int l, int r) {
  size_t version = v->version;
  v = copy(v);
  v->version = version + 1;
  // copy_count = 0;
  auto [a, b] = split(v, l);
  auto [c, d] = split(b, r - l + 1);
  // cout << copy_count << endl;
  auto result = c->sum;
  v = merge(a, merge(c, d));
  return result;
}

void set(NodePtr& v, int index, char ch) {
  size_t version = v->version;
  v = copy(v);
  v->version = version + 1;
  auto [a, b] = split(v, index);
  auto [c, d] = split(b, 1);
  c->value = ch;
  update(c);
  v = merge(a, merge(c, d));
}

template <typename T, size_t n>
ostream& operator<<(ostream& out, const array<T, n>& arr) {
  for (const auto& i: arr)
    out << i << " ";
  return out << "\n";
}

int main() {

  // while (true) {
  // Test();

  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<NodePtr> v;
  v.reserve(1e4);
  while (n--) {
    string s;
    cin >> s;
    NodePtr root = nullptr;
    for (const auto& c : s)
      root = merge(root, new Node(c, v.size()));
    v.push_back(root);
  }
  cin >> n;
  int q_num = 0;
  while (n--) {
    char q;
    cin >> q;
    if (q == '?') {
      int i, l, r;
      cin >> i >> l >> r;
      cout << sum(v[i - 1], l - 1, r - 1);
    } else if (q == '=') {
      int i, j;
      char c;
      cin >> i >> j >> c;
      set(v[i - 1], j - 1, c);
    } else if (q == 'X') {
      int i1, i2, j1, j2;
      cin >> i1 >> i2 >> j1 >> j2;
      auto [l, r] = cut_swap(v[i1 - 1], v[i2 - 1], j1, j2, v.size(), v.size() + 1);
      v.push_back(l);
      v.push_back(r);
    }
    // cout << ++q_num << endl;
  }
  // }

}