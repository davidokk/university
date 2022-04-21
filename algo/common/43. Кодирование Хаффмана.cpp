#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
  ifstream cin("huffman.in");
  ofstream cout("huffman.out");

  int n;
  cin >> n;

  long long ans = 0;
  priority_queue<long long, vector<long long>, greater<>> q;
  while (n--) {
    int x;
    cin >> x;
    q.push(x);
  }

  while (q.size() != 1) {
    long long x = q.top();
    q.pop();
    long long y = q.top();
    q.pop();
    ans += x + y;
    q.push(x + y);
  }

  cout << ans;

  return 0;
}