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

  using NodePtr = shared_ptr<Node>;

  NodePtr root;

  void Add(int value) {
    NodePtr* ptr = &root;
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

  long long Sum() const { return Sum(root); }

  void PreOrderTraversal(std::ostream& out) const { PreOrderTraversal(out, root); }

  void Remove(int value) {
    NodePtr parent;
    NodePtr v = root;
    while (v != nullptr && v->value != value) {
      parent = v;
      v = value < v->value ? v->left : v->right;
    }
    if (v && v->left && v->right)
      RemoveTwoSubTree(v);
    else if (v)
      RemoveOneSubTree(parent, v);
  }

 private:
  void RemoveOneSubTree(const NodePtr& parent, const NodePtr& v) {
    NodePtr* p;
    if (parent == nullptr)
      p = &root;
    else
      p = (v->value < parent->value ? &parent->left : &parent->right);
    *p = v->left != nullptr ? v->left : v->right;
  }

  void RemoveTwoSubTree(const NodePtr& v) {
    NodePtr parent = v;
    NodePtr w = v->right;
    while (w->left != nullptr) {
      parent = w;
      w = w->left;
    }
    v->value = w->value;
    RemoveOneSubTree(parent, w);
  }

  long long Sum(const NodePtr& v) const {
    if (v == nullptr)
      return 0;
    return v->value + Sum(v->left) + Sum(v->right);
  }

  void PreOrderTraversal(std::ostream& out, const NodePtr& v) const {
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

  int to_remove, a;
  in >> to_remove;

  while (in >> a)
    t.Add(a);
  t.Remove(to_remove);

  ofstream out("output.txt");
  t.PreOrderTraversal(out);

  return 0;
}