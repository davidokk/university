#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

struct Tree {
  struct Node {
    int value;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    explicit Node(int val) { value = val; }
  };

  shared_ptr<Node> root;

  void Add(int value) {
    shared_ptr<Node>* ptr = &root;
    while (*ptr != nullptr) {
      if ((*ptr)->value > value)
        ptr = &(*ptr)->left;
      else if ((*ptr)->value < value)
        ptr = &(*ptr)->right;
      else
        return;
    }
    *ptr = make_shared<Node>(value);
  }

  long long Sum() { return Sum(root); }

 private:
  long long Sum(const shared_ptr<Node>& v) {
    if (v == nullptr)
      return 0;
    return v->value + Sum(v->left) + Sum(v->right);
  }

};

int main() {

  Tree t;
  ifstream in("input.txt");
  int a;
  while (in >> a)
    t.Add(a);

  ofstream out("output.txt");
  out << t.Sum();

  return 0;
}