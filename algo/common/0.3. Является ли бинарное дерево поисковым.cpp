#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
  int value;
  long long left_border = INT_MIN - 1ll;
  long long right_border = INT_MAX + 1ll;
};

string Solution() {
  ifstream in("bst.in");

  vector<Node> nodes(1);
  int n, m, p;
  char c;
  in >> n;
  in >> m;
  nodes.reserve(n + 1);
  nodes.push_back(Node{m});

  for (int i = 0; i < n - 1; ++i) {
    in >> m >> p >> c;

    nodes.push_back({m, nodes[p].left_border, nodes[p].right_border});
    Node& parent = nodes[p];
    Node& v = nodes.back();
    if (c == 'L') {
      v.right_border = parent.value;
    } else {
      v.left_border = parent.value;
    }
    if (v.value < v.left_border || v.value >= v.right_border)
      return "NO";
  }
  return "YES";
}

int main() {

  ofstream out("bst.out");
  out << Solution();

  return 0;
}