#include <iostream>
#include <vector>

using namespace std;

int m = 1e9 + 7;

long long pow(long long n, int k) {
  if (k == 0)
    return 1;
  if (k & 1)
    return (n % m * pow(n, k - 1) % m) % m;
  long long a = pow(n, k >> 1);
  return (a * a) % m;
}

int main() {

  int n, k;
  cin >> n >> k;

  vector<long long> fact(n + 1, 1);

  for (int i = 1; i <= n; ++i)
    fact[i] = (fact[i - 1] * i) % m;

  cout << (fact[n] * pow((fact[n - k] * fact[k]) % m, m - 2)) % m;

  return 0;
}