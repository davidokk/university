#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct MyClass {
  friend ostream& operator<< (ostream& os, const MyClass& m) {
    return os << "{" << m.n << "," << m.s << "}";
  }
  bool operator==(const MyClass& other) const { return n == other.n && s == other.s; }

  explicit MyClass(int N) : n(N) {}
  MyClass(int N, const string& S) : n(N), s(S) {}

  int n;
  string s;
};

// оператор вывода в поток для unordered_map
template <class K, class V, class Hasher, class Equal>
ostream& operator << (ostream& os, const unordered_map<K, V, Hasher, Equal>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

int main() {

  // 1. unordered_map словарь с неупорядоченными ключами, представляет
  // собой хеш таблицу. Для каждого элемента вычисляется хеш и номер его корзины,
  // обычно корзина это std::list. Номер корзины у разных элементов может совпадать,
  // это называется коллизией. Тогда элемент добавляется в конец списка

  // 2. Тип итератора ForwardIterator (есть ++ и *)
  // const_iterator запрещает менять значение в ключе
  // iterator(value_type&) const_iterator(const value_type&)

  // 3. Конструкторы
  //  1) explicit unordered_map( size_type bucket_count ) от числа корзин
  //  2) template< class InputIt >
  //     unordered_map( InputIt first, InputIt last ) от диапазона, заданного двумя итераторами
  //  3) unordered_map( const unordered_map& other ) копирующий
  //  4) unordered_map( unordered_map&& other ) перемещающий
  //  5) unordered_map( std::initializer_list<value_type> init ) от списка инициализации

  // 4. Класс, которым мы параметризуем unordered_map, должен иметь
  // operator== и собственный хешер - функциональный объект с оператором(),
  // возвращающим size_t
  {

    struct Hasher {
      explicit Hasher(int x) {}
      size_t operator()(const MyClass& a) const { return 41 * hi(a.n); }
      hash<string> hs;
      hash<int> hi;
    };

    struct Equal {
      bool operator()(const MyClass& a, const MyClass& b) const {
        return a.n == b.n;
      }
    };
    unordered_map<MyClass, MyClass, Hasher, Equal> mp(10, Hasher(1));

    mp.insert(make_pair(MyClass{1, "1"}, MyClass{1, "1"}));
    mp.emplace(piecewise_construct, make_tuple(1, "2"), make_tuple(1, "1"));

    cout << mp << endl;
  }

  // 5. Для внутренниъ методов, например, find, count, equal_range нужны также хешер и operator==

  // 6. Копирующий вызывается при передаче аргумента в функцию по значению,
  // а перемешающий при возвращении локальной переменной из функции (идиома NRVO)
  {
    auto reverse = [](unordered_map<int, int> mp)->unordered_map<int, int> {
      unordered_map<int, int> result;
      for (auto[key, value] : mp)
        result[value] = key;
      return result;
    };
    unordered_map<int, int> a{{1, 2}, {3, 4}};
    auto reversed = reverse(a);
  }

  // 7. emplace методы
  {
    unordered_map<int, int> a;
    a.emplace(1, 2); // = a[1] = 2;
  }

  // 8. Т.к нам нужно сравнивать пары алгоритмы find, count и т.д не будут работать,
  // но будут работать find_if и count_if за O(n).
  // Для того, чтобы алгоритмы работали нужно определить нужные операторы для std::pair.
  // Т.к. итераторы в unordered_map типа forward, не будет работать, например,
  // алгоритм sort или binary_search так как они требуют random тип итераторов
  {
    unordered_map<int, int> a{{1, 1}, {4, 2}, {3, 3}}, b;
    auto it = std::find_if(a.begin(), a.end(), [](const pair<int, int>& p) {
      return p.second == 2;
    });
  }

  // 9. Этот контейнер следует использовать, когда не нужно поддерживать
  // ключи в отсортированном виде. Тогда достигается сложность О(1) вставки, удаления и поиска.

  // 10. Получить хеш функционального объекта невозможно
  // поэтому использовать их как ключи в unordered_map нельзя

  // 11. Задача, например, найти самое частовстречаемое слово в тексте.
  // Для этого нам не нужно поддерживать алфавитный порядок.

  // 12. При вставке или удалении может произойти рехеширование
  // и при этом итераторы инвалидируются

  {
    unordered_map<int, int> m;
    m[1] = 2;
    m[2] = 4;
    m[1] = 3;
    cout << m;
  }

  return 0;
}
