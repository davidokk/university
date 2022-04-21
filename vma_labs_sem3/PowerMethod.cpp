#include <cmath>
#include <algorithm>

#include "PowerMethod.h"

using namespace std;

float PowerMethod::ScalarMultiplication(const vector<float>& vec1, const vector<float>& vec2) {
  float answer = 0;
  for (int i = 0; i < vec1.size(); ++i)
    answer += vec1[i] * vec2[i];
  return answer;
}

vector<float> PowerMethod::Difference(const vector<float>& y1, float l1, const vector<float>& y2) {
  vector<float> source;
  source.reserve(y1.size());
  for (int i = 0; i < y1.size(); ++i)
    source.push_back(y1[i] - l1 * y2[i]);
  return source;
}

int PowerMethod::MaxNorm(const vector<float>& v) {
  return max_element(v.begin(), v.end(),
    [](float a, float b){return fabs(a) < fabs(b); }) - v.begin();
}

void PowerMethod::IterativePowerAlgorithm() {
  vector<float> u(a.size());
  u[0] = 1;
  vector<float> v = MatrixMultiplyByVector(a, u);
  float l1_1, l1_2;
  for (int i = 0; i < 50; ++i) {
    u = v;
    float norm = sqrt(ScalarMultiplication(v, v));
    for (int j = 0; j < u.size(); ++j)
      u[j] /= norm;
    int max_ind = MaxNorm(v);
    v = MatrixMultiplyByVector(a, u);
    l1_1 = v[max_ind] / u[max_ind];
    l1_2 = ScalarMultiplication(v, u) / ScalarMultiplication(u, u);
    if (i >= 45) {
      out << endl << "итерация " << i + 1 << ":\n";
      out << "l1 по формуле 1 = " << l1_1 << endl << "l1 по формуле 2 = " << l1_2 << endl << "vector = ";
      PrintColumn(Difference(v, l1_1, u));
    }
  }
  out << "\nМаксимум норма: " << MaxNorm(Difference(v, l1_1, u));
}

void Lab6Task1::Solve() {
  GenerateMatrix();
  out << endl;
  PrintMatrix();
  IterativePowerAlgorithm();
}
