#include <iostream>
#include <vector>

using namespace std;

int main() {

  int n;
  cin >> n;
  vector<int> sum(3, -1), prev(n + 3);
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    sum.push_back(a);
  }

  prev[3] = -1;
  for (int i = 4; i < n + 3; ++i) {
    if (sum[i - 2] > sum[i - 3]) {
      sum[i] += sum[i - 2];
      prev[i] = i - 2;
    } else if (sum[i - 3] != -1) {
      sum[i] += sum[i - 3];
      prev[i] = i - 3;
    } else {
      sum[i] = -1;
    }
  }

  cout << sum.back() << endl;

  if (sum.back() != -1) {
    vector<int> ans;
    int i = (int) sum.size() - 1;
    while (i != -1) {
      ans.push_back(i - 2);
      i = prev[i];
    }

    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
      cout << *it << " ";
  }

  return 0;
}