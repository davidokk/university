#include <iostream>

using namespace std;

long long fact(int a) {
	if (a == 0)
		return 1;
	return a * fact(a - 1);
}

int Sum(int n, int m) {
	return fact(5 * n) * fact(5 * m) / fact(m) / fact(n) / fact(3 * m + n) / fact(3 * n + m);
}

int SumLinear(int n_, int m_) {
	long long dnm = 1; 
	for (int m = 1; m <= m_; ++m) {
		dnm *= 5 * (5 * m - 1) * (5 * m - 2) * (5 * m - 3) * (5 * m - 4);
		dnm /= m * 3 * m * (3 * m - 1) * (3 * m - 2);
	}

	for (int n = 1; n <= n_; ++n) {
		dnm *= 5 * (5 * n - 1) * (5 * n - 2) * (5 * n - 3) * (5 * n - 4);
		dnm /= (3 * m_ + n) * (3 * n + m_) * (3 * n + m_ - 1) * (3 * n + m_ - 2);
	}

	return dnm;
}

int SumASM(int n, int m) {
	_asm {
		mov eax, 1

		mov ecx, m
		jecxz s1
		mov ecx, 1
		inc m
		cycle:
			mov ebx, 5
			imul ebx
			imul ebx, ecx

			push ecx 
			mov ecx, 4
			cycle1:
				dec ebx 
				imul ebx 
			loop cycle1
			pop ecx
	
			xor edx, edx
			mov ebx, ecx 
			idiv ebx
			imul ebx, 3
			push ecx 
			mov ecx, 3
			cycle2:
				idiv ebx
				dec ebx 
			loop cycle2 
			pop ecx

		inc ecx
		cmp ecx, m
		jne cycle

		s1:

		mov ecx, n
		jecxz s2
		inc n
		mov ecx, m
		jecxz s
		dec m 
		s:
		mov ecx, 1
		cycle3:
			mov ebx, 5
			imul ebx 
			imul ebx, ecx
			push ecx 
			mov ecx, 4
			cycle4: 
				dec ebx
				imul ebx
			loop cycle4
			pop ecx

			mov ebx, 3
			imul ebx, m		
			add ebx, ecx
			idiv ebx

			mov ebx, 3
			imul ebx, ecx
			add ebx, m
			push ecx
			mov ecx, 3
			cycle5:
				idiv ebx 
				dec ebx
			loop cycle5
			pop ecx

		inc ecx 
		cmp ecx, n
		jne cycle3

		s2:
	}
}

int main() {
	int n, m; 
	cout << "Enter n, m: ";
	cin >> n >> m; 

	cout << Sum(n, m) << endl;
	cout << "C++: " << SumLinear(n, m) << endl;
	cout << "ASM: " << SumASM(n, m);
}