#pragma once

#include <iostream>
#include <stack>
#include <queue>

template<typename T>
class SearchTree {
 public:
  struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  SearchTree() : root(nullptr) {}
  SearchTree(std::initializer_list<T>);
  SearchTree(const SearchTree<T>& tree);
  SearchTree<T>& operator= (const SearchTree<T>& tree);
  SearchTree(SearchTree<T>&& tree) noexcept;
  SearchTree<T>& operator= (SearchTree<T>&& tree) noexcept;

  ~SearchTree() { Clear(); }

  void Insert(T value);
  const Node* Find(T value) const;
  bool Delete(T value);
  void Clear() { Clear(root); root = nullptr; }
  friend void Swap(SearchTree<T>& l, SearchTree<T>& r) { std::swap(l, r); }

  int Size() const { return Size(root); }  // O(n)
  int Depth() const { return Depth(root); }  // O(n)

  bool IsLeaf(Node* node) const;
  bool Contains(T value) { return Find(value) != nullptr; }

  void Print(std::ostream& os) const { Print(os, root); }
  void SortedPrint(std::ostream& os) const { SortedPrint(os, root); }
  friend std::ostream& operator<<(std::ostream& os, const SearchTree<T>& t) { t.Print(os); return os; }

  struct Subtree {
    Node* root = nullptr;
    size_t size = 0;
    bool condition = true;
  };

  // лаба 8.1
  // рекурсивная
  Subtree Go(Node* node, Subtree& answer) const {
    if (!node)
      return Subtree{};

    Subtree left = Go(node->left, answer);
    Subtree right = Go(node->right, answer);
    size_t size = left.size + right.size + 1;

    if (IsLeaf(node) || (left.condition && right.condition && left.size > right.size)) {
      if (size > answer.size)
        answer = {node, size};
      return {node, size, true};
    }
    return {node, size, false};
  }
  Subtree MaxSubtreeRec() const {
    Subtree answer{};
    Go(root, answer);
    return answer;
  }

  // нерекурсивная
  Subtree MaxSubtreeIter() const {
    Subtree ans{nullptr, 0, false};

    Node* v = root;
    Node* prev = nullptr;
    std::stack<Subtree> S;
    int s = 0;
    int c = false;

    while (true) {
      while ( v ) { S.push(Subtree{v}); v = v->left; }
      if ( S.empty() ) break;
      v = S.top().root;
      if (v->right && (v->right != prev))
        { S.top().size = s; S.top().condition = c; v = v->right; s = 0; c = false; }
      else {
        prev = v;
        v = nullptr;
        int ls = S.top().size;
        int rs = s;
        if (!prev->right)
          std::swap(ls, rs);
        if (IsLeaf(prev))
          { c = 1; }
        else
          { c = std::min<bool>(c, S.top().condition); }
        //std::cout << "root: " << prev->value << std::endl;
        //std::cout << "ls: " << ls << std::endl;
        //std::cout << "rs: " << rs << std::endl;
        s += S.top().size + 1;
        S.pop();
        if ( c && (ls > rs || IsLeaf(prev)) ) {
          if (ans.size < s)
            ans = Subtree{prev, s, true};
          //std::cout << ls << " " << rs << " " << prev->value << std::endl;
        }
      }
    }
    return ans;
  }

 private:
  Node* root;

  int Size(Node* node) const;
  int Depth(Node* node) const;
  void Print(std::ostream& os, Node* node) const;
  void SortedPrint(std::ostream& os, Node* node) const;
  void Clear(Node* node);
  void Copy(Node* node, SearchTree<T>& new_tree) const;
};

template<typename T>
void SearchTree<T>::Insert(T value) {
  Node** p = &root;
  while (*p) {
    if ((*p)->value < value)
      p = &((*p)->right);
    else
      p = &((*p)->left);
  }
  *p = new Node{value};
}

template<typename T>
SearchTree<T>::SearchTree(std::initializer_list<T> l) : SearchTree() {
  for (const auto& element : l)
    Insert(element);
}

template<typename T>
int SearchTree<T>::Size(Node* node) const {
  if (!node)
    return 0;
  return Size(node->left) + Size(node->right) + 1;
}

template<typename T>
void SearchTree<T>::Print(std::ostream& os, Node* node) const {
  if (!node) return;
  os << node->value << " "; Print(os, node->left); Print(os, node->right);
}

template<typename T>
void SearchTree<T>::SortedPrint(std::ostream& os, Node* node) const {
  if (!node) return;
  SortedPrint(os, node->left); os << node->value << " "; SortedPrint(os, node->right);
}

template<typename T>
int SearchTree<T>::Depth(Node* node) const {
  if (!node)
    return 0;
  return std::max(Depth(node->left), Depth(node->right)) + 1;
}

template<typename T>
bool SearchTree<T>::IsLeaf(Node* node) const {
  if (!node)
    return false;
  return !node->left && !node->right;
}

template<typename T>
const typename SearchTree<T>::Node* SearchTree<T>::Find(T value) const {
  Node* ptr = root;
  while (ptr && ptr->value != value) {
    if (value < ptr->value)
      ptr = ptr->left;
    else
      ptr = ptr->right;
  }
  return ptr;
}

// template<typename T>
// bool SearchTree<T>::Delete(T value) {
//
// }

template<typename T>
void SearchTree<T>::Clear(Node* node) {
  if (!node)
    return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}

template<typename T>
void SearchTree<T>::Copy(Node* node, SearchTree<T>& new_tree) const {
  if (!node)
    return;
  new_tree.Insert(node->value);
  Copy(node->left, new_tree);
  Copy(node->right, new_tree);
}

template<typename T>
SearchTree<T>::SearchTree(const SearchTree<T>& tree) : SearchTree() {
  tree.Copy(tree.root, *this);
}

template<typename T>
SearchTree<T>::SearchTree(SearchTree<T>&& tree) noexcept {
  root = tree.root;
  tree.root = nullptr;
}

template<typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree<T>& tree) {
  if (this == &tree)
    return *this;
  auto temp(tree);
  Swap(*this, temp);
}

template<typename T>
SearchTree<T>& SearchTree<T>::operator=(SearchTree<T>&& tree) noexcept {
  if (this == &tree)
    return *this;
  auto temp(std::move(tree));
  Swap(*this, temp);
}
