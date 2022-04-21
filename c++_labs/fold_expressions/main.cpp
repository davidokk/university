#include "KRat.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

template<typename Container, typename ...Args>
bool OneHere(const Container& container, Args... args) {
  return ((std::count(container.begin(), container.end(), args) != 0) || ...);
}

template<typename T, typename ...Args>
bool Insert(std::set<T>& set, Args... args) {
  return (set.insert(args).second & ...);
}

template<typename Container, typename ...Args>
bool AllHere(const Container& container, Args... args) {
  return ((std::count(container.begin(), container.end(), args) != 0) && ...);
}

template<typename Container, typename ...Args>
void PushBack(Container& container, Args... args) {
  (container.push_back(args), ...);
}

int main() {

  // std::vector<KRat> k{{1, 2}, {2, 3}, {5, 6}};
  // std::cout << AllHere(k, KRat{2, 3}, KRat{1, 2}) << endl;
  //
  // std::vector<int> v{1, 2, 3};
  // std::cout << std::boolalpha << OneHere(v, 1, 4, 7) << std::endl;

  std::set<int> a{1};
  std::cout << Insert(a, 2, 3, 4) << std::endl;
  std::cout << Insert(a, 2, 5) << std::endl;  
  for (const auto& i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  // std::cout << AllHere(v, 1, 2, 3, 2) << std::endl;
  //
  // PushBack(v, 4, 5, 6, 1, 1, 1);
  // for (const auto& i : v)
  //   std::cout << i << " ";

  return 0;
}
