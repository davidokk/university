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

  void PreOrderTraversal(std::ostream& out) { return PreOrderTraversal(out, root); }

 private:
  long long Sum(const shared_ptr<Node>& v) {
    if (v == nullptr)
      return 0;
    return v->value + Sum(v->left) + Sum(v->right);
  }

  void PreOrderTraversal(std::ostream& out, shared_ptr<Node>& v) {
    if (v != nullptr) {
      out << v->value << "\n";
      PreOrderTraversal(out, v->left);
      PreOrderTraversal(out, v->right);
    }
  }

};

int main() {

  Tree t;
  ifstream in("input.txt");
  int a;
  while (in >> a)
    t.Add(a);

  ofstream out("output.txt");
  t.PreOrderTraversal(out);

  return 0;
}