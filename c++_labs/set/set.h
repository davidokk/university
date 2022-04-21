// тип T должен иметь operator< и operator==

// итератор
// emplace-метод
// конструктор через итераторы

#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class ProxySet;

template<typename T>
class SetIterator;

template<typename T>
class Set {
  friend class SetIterator<T>;
 public:
  Set() = default;
  Set(std::initializer_list<T> list);

  template<typename Iterator>
  Set(Iterator begin, Iterator end) {
    while (begin != end)
      set.push_back(*begin++);
    SortAndDeleteDuplicates();
  }

  template<typename Container>
  Set(Container container) : Set(container.begin(), container.end()) {}

  Set(const Set<T>& s) = default;
  Set& operator=(const Set<T>& s) = default;

  Set(Set<T>&& s) noexcept = default;
  Set& operator=(Set<T>&& s) noexcept = default;

  ~Set() = default;

  template<typename ...Args>
  void emplace_insert(Args&&... args) {
    set.push_back(T(args...));
    SortAndDeleteDuplicates();
  }

  size_t Size() const;
  void Clear();
  friend void Swap(Set& a, Set& b) { std::swap(a.set, b.set); }

  Set operator+(const Set& r) const;
  Set& operator+=(const Set& r);

  Set operator-(const Set& r) const;
  Set& operator-=(const Set& r);

  Set operator*(const Set& r) const;
  Set& operator*=(const Set& r);

  Set operator/(const Set& r) const;
  Set& operator/=(const Set& r);

  bool operator==(const Set& r) const { return set == r.set; }
  bool operator!=(const Set& r) const { return !operator==(r); }
  bool operator<=(const Set& r) const { return *this * r == *this; }
  bool operator>(const Set& r) const { return *this * r == r && *this * r != *this; }
  bool operator>=(const Set& r) const { return r.operator<=(*this); }
  bool operator<(const Set& r) const { return r.operator>(*this); }

  ProxySet<T> operator[](const Set& r) const { return ProxySet<T>((Set&)*this, *this * r); }

  SetIterator<T> begin() { return SetIterator<T>((Set&)*this, 0); }
  SetIterator<T> end() { return SetIterator<T>((Set&)*this, Size()); }

  SetIterator<T> begin() const { return SetIterator<T>((Set&)*this, 0); }
  SetIterator<T> end() const { return SetIterator<T>((Set&)*this, Size()); }

  friend std::istream& operator>>(std::istream& is, Set& s) {
    s.set.clear();
    int n;
    is >> n;
    while (n--) {
      T x;
      is >> x;
      s.set.push_back(x);
    }
    s.SortAndDeleteDuplicates();
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const Set& s) {
    os << "{";
    bool first = true;
    for (auto item : s.set) {
      if (!first)
        os << ", ";
      first = false;
      os << item;
    }
    return os << "}";
  }

 private:
  T& operator[](int index) { return set[index]; }
  void SortAndDeleteDuplicates();
  std::vector<T> set;
};

template<typename T>
class ProxySet {
 public:
  ProxySet(Set<T>& new_set, const Set<T>& new_del);

  operator Set<T>() const;

  Set<T> operator= (const Set<T>& r);

  friend std::ostream& operator<< (std::ostream& os, const ProxySet& r) { return os << Set<T>(r); }
 private:
  Set<T>& set;
  Set<T> del;
};

template<typename T>
class SetIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = T*;
  using refernce = T&;

  SetIterator(Set<T>& s, size_t idx) : set(s), index(idx) {}

  SetIterator<T>& operator= (const SetIterator<T>& it) {
    set = it.set;
    index= it.index;
    return *this;
  }

  const T& operator*() const {
    if (*this == set.end()) throw std::runtime_error("Dereferencing end pointer");
    return set[index];
  }

  SetIterator& operator++() {
    if (*this == set.end()) throw std::runtime_error("operator++ for end pointer");
    ++index; return *this;
  }
  SetIterator operator++(int) {
    if (*this == set.end()) throw std::runtime_error("operator++ for end pointer");
    auto it = *this; ++index; return it;
  }
  SetIterator& operator--() {
    if (*this == set.begin()) throw std::runtime_error("operator-- for begin pointer");
    --index; return *this;
  }
  SetIterator operator--(int) {
    if (*this == set.begin()) throw std::runtime_error("operator-- for begin pointer");
    auto it = *this; --index; return it;
  }

  bool operator==(const SetIterator<T>& r) const { return index == r.index && set == r.set; }
  bool operator!=(const SetIterator<T>& r) const { return !operator==(r); }

 private:
  Set<T>& set;
  size_t index;
};

template<typename T>
ProxySet<T>::ProxySet(Set<T>& new_set, const Set<T>& new_del) : set(new_set), del(new_del) {}

template<typename T>
ProxySet<T>::operator Set<T>() const { return Set<T>(del); }

template<typename T>
Set<T> ProxySet<T>::operator=(const Set<T>& r) {
  set /= del;
  set += r;
  return set;
}

template<typename T>
Set<T>::Set(std::initializer_list<T> list) {
  for (const auto& item : list)
    set.push_back(item);
  SortAndDeleteDuplicates();
}

template<typename T>
void Set<T>::SortAndDeleteDuplicates() {
  sort(set.begin(), set.end());
  set.erase(unique(set.begin(), set.end()), set.end());
}

template<typename T>
size_t Set<T>::Size() const { return set.size(); }

template<typename T>
void Set<T>::Clear() { set.clear(); }

template<typename T>
Set<T> Set<T>::operator+(const Set<T>& r) const {
  Set<T> ans;
  int i = 0, j = 0;
  int n = this->Size(), m = r.Size();
  while (i != n || j != m) {
    int push;
    if (i != n && (j == m || set[i] < r.set[j])) {
      push = set[i];
      i++;
    } else {
      push = r.set[j];
      j++;
    }
    if (ans.set.empty() || ans.set.back() != push)
      ans.set.push_back(push);
  }
  return ans;
}

template<typename T>
Set<T>& Set<T>::operator+=(const Set<T>& r) { return *this = *this + r; }

template<typename T>
Set<T> Set<T>::operator-(const Set<T>& r) const {
  Set ans = (*this / r) + (r / *this);
  return ans;
}

template<typename T>
Set<T>& Set<T>::operator-=(const Set<T>& r) { return *this = *this - r; }

template<typename T>
Set<T> Set<T>::operator*(const Set<T>& r) const {
  Set ans;
  for (auto& item : set)
    if (binary_search(r.set.begin(), r.set.end(), item))
      ans.set.push_back(item);
  return ans;
}

template<typename T>
Set<T>& Set<T>::operator*=(const Set<T>& r) { return *this = *this * r; }

template<typename T>
Set<T> Set<T>::operator/(const Set<T>& r) const {
  Set ans;
  for (auto& item : set)
    if (!binary_search(r.set.begin(), r.set.end(), item))
      ans.set.push_back(item);
  return ans;
}

template<typename T>
Set<T>& Set<T>::operator/=(const Set<T>& r) { return *this = *this / r; }
