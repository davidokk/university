#include <iostream>

using namespace std;

extern "C" void DeleteSpace(char* s, int n);

int main() {
	char str[] = "";
	DeleteSpace(str, strlen(str));
	cout << "#" << str << "#"; 
}