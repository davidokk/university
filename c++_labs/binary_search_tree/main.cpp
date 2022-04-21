#include "search_tree.h"

#include <iostream>

using namespace std;

SearchTree<int> ReadTree() {
  SearchTree<int> tree;
  cout << "Enter n: ";
  int n;
  cin >> n;
  cout << "Enter " << n << " elements:\n";
  while (n--) {
    int x;
    cin >> x;
    tree.Insert(x);
  }
  cout << "---------------------\n";
  return tree;
}

size_t test = 1;

void Test(const SearchTree<int>& tree) {
  cout << "Test " << test++ << "\nTree: " << tree << endl;
  cout << "---------------------\n";
  cout << "Rec:\n";
  auto answer = tree.MaxSubtreeRec();
  if (answer.root == nullptr)
    cout << "Tree is empty\n";
  else
    cout << "Subtree's root is " << answer.root->value << " \nSubtree size: "
         << answer.size << endl;
  cout << "---------------------\n";
  cout << "Iter:\n";

  answer = tree.MaxSubtreeIter();
  if (answer.root == nullptr)
    cout << "Tree is empty\n";
  else
    cout << "Subtree's root is " << answer.root->value << " \nSubtree size: "
         << answer.size << endl;
  cout << "---------------------\n";
}

int main() {

  // задача - в бинарном дереве поиска найти максимальное поддерево
  // с наибольшим числом вершин, в котором для каждой нелистьевой вершины
  // число вершин в левом поддереве больше числа вершин в правом поддереве.

  Test(SearchTree{20});
  //Test(SearchTree{0, -1, 10, 5, 6, 4, 3, 15, 14, 17, 2, 12});
  //Test(SearchTree{10, 2, 5, 12});
  //Test(SearchTree{10, 20});
  //Test(SearchTree<int>{});
  //Test(SearchTree{10, 8, 9, 14, 16, 12, 17, 7, 6, 15, 13, 11});
  //Test(SearchTree{7, 20, 15});
  //Test(SearchTree{123});
  //Test(ReadTree());

  return 0;
}
