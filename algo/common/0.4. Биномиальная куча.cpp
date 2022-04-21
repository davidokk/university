#include <iostream>
#include <fstream>

using namespace std;

int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  long long n;
  cin >> n;

  int i = 0;
  while (n) {
    if (n & 1)
      cout << i << "\n";
    n >>= 1;
    ++i;
  }

}