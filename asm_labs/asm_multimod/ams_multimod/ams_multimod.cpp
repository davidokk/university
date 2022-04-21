#include <iostream>
#include <bitset>

extern "C" void __fastcall InvertMatrixFastCall(int*, int, int);

int* read(int n, int m) {
	int* a = new int[n * m];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			std::cin >> a[i * m + j];
	}
	return a;
}

void print(int* a, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			std::cout << a[i * m + j] << " ";
		std::cout << std::endl;
	}
}

int main() {

	std::cout << "enter N, M: ";
	int n, m;
	std::cin >> n >> m;
	std::cout << "enter NxM elemets:\n";

	int* a = read(n, m);
	InvertMatrixFastCall(a, n, m);
	std::cout << "Inverted matrix:" << std::endl;
	print(a, n, m);

}
