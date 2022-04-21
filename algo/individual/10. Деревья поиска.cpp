#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

using namespace std;

struct Node;

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

  int height;
  int ways;

  Node(int val, Node* p) { value = val; parent = p; }
};

int Height(Node* v) {
  return v != nullptr ? v->height : -1;
}
int Ways(Node* v) {
  return v != nullptr ? v->ways : -1;
}
int SemiPath(Node* v) {
  if (v == nullptr)
    return 0;
  return Height(v->left) + Height(v->right) + 2;
}
Node* MoreDepth(Node* v) {
  return Height(v->left) > Height(v->right) ? v->left : v->right;
}

struct Tree {
  Node* root = nullptr;
  int max_semi_path = -1;

  void FirstTraversal(Node* v) {
    if (v == nullptr)
      return;
    FirstTraversal(v->left);
    FirstTraversal(v->right);
    int l = Height(v->left), r = Height(v->right);
    v->height = max(l, r) + 1;
    v->ways = max(1, (l >= r) * Ways(v->left) + (r >= l) * Ways(v->right));
    max_semi_path = max(max_semi_path, SemiPath(v));
  }

  void GoWhileOne(Node* v) {
    if (!v)
      return;
    Node* vv = MoreDepth(v);
    if (Ways(v) == Ways(vv))
      GoWhileOne(vv);
    Remove(v);
  }

  void Solve() {
    FirstTraversal(root);
    Node* v = root;
    int k = SemiPath(v) == max_semi_path;
    while (Height(v->left) != Height(v->right)) {
      v = MoreDepth(v);
      k += SemiPath(v) == max_semi_path;
    }
    while (SemiPath(v) != max_semi_path)
      v = v->parent;

    if (k == 1) {
      GoWhileOne(v->left);
      GoWhileOne(v->right);
      Remove(v);
    } else {
      if (Height(v->left) == Height(v->right))
        Remove(v);
      else {
        GoWhileOne(MoreDepth(v));
        Remove(v);
      }
    }
  }

  void Add(int value) {
    Node** ptr = &root;
    Node* parent = nullptr;
    while (*ptr != nullptr) {
      parent = *ptr;
      if ((*ptr)->value > value)
        ptr = &(*ptr)->left;
      else if ((*ptr)->value < value)
        ptr = &(*ptr)->right;
      else
        return;
    }
    *ptr = new Node(value, parent);
  }

  void PreOrderTraversal(ostream& out, Node* v) const {
    if (v) {
      out << v->value << "\n";
      PreOrderTraversal(out, v->left);
      PreOrderTraversal(out, v->right);
    }
  }

  void Print(ostream& out) const { PreOrderTraversal(out, root); }

  void Remove(Node* v) {
    if (v == nullptr)
      return;
    if (v->left && v->right)
      RemoveTwoSubTree(v);
    else
      RemoveOneSubTree(v->parent, v);
  }

 private:
  void RemoveOneSubTree(Node* parent, Node* v) {
    Node** p;
    if (parent == nullptr)
      p = &root;
    else
      p = (v->value < parent->value ? &parent->left : &parent->right);
    *p = v->left != nullptr ? v->left : v->right;
  }

  void RemoveTwoSubTree(Node* v) {
    Node* parent = v;
    Node* w = v->right;
    while (w->left != nullptr) {
      parent = w;
      w = w->left;
    }
    v->value = w->value;
    RemoveOneSubTree(parent, w);
  }

};

int main() {

  Tree t;
  ifstream in("in.txt");
  int a;
  while (in >> a)
    t.Add(a);

  t.Solve();

  ofstream out("out.txt");
  t.Print(out);

  return 0;
}