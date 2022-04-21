#include <iostream> 

int P1(int f0, int f1, int f2, int n, int x) {
    int p1 = 0;
    if (n >= 0) {
        p1 *= x;
        p1 += f0;
    }
    if (n >= 1) {
        p1 *= x;
        p1 += f1;
    }
    if (n >= 2) {
        p1 *= x; 
        p1 += f2;
    }
    for (int i = 3; i <= n; i++) {
        int f = 3 * f2 * f1 - 4 * f0;
        f0 = f1;
        f1 = f2;
        f2 = f;
        p1 *= x;
        p1 += f2; 
    }
    return p1;
}
int P1_ASM(int f0, int f1, int f2, int n, int x) {
    __asm {
        mov eax, 0
        cmp n, 0
        jl s
        imul eax, x
        add eax, f0
        s :
        cmp n, 1
            jl s1
            imul eax, x
            add eax, f1
            s1 :
        cmp n, 2
            jl s2
            imul eax, x
            add eax, f2
            s2 :

        cmp n, 2
            jle s3
            c :
        mov ecx, 3
            imul ecx, f2
            imul ecx, f1
            mov edx, 4
            imul edx, f0
            sub ecx, edx

            mov edx, f1
            mov f0, edx
            mov edx, f2
            mov f1, edx
            mov f2, ecx
            
            imul eax, x
            add eax, ecx

            sub n, 1
            cmp n, 2
            jne c

            s3 :
    }
}

int P2(int f0, int f1, int f2, int n, int x) {
    int p2 = 0; int q = 1;
    if (n >= 0) {
        p2 += f0 * q;
        q *= x;
    }
    if (n >= 1) {
        p2 += f1 * q;
        q *= x;
    }
    if (n >= 2) {
        p2 += f2 * q;
        q *= x;
    }
    for (int i = 3; i <= n; i++) {
        int f = 3 * f2 * f1 - 4 * f0;
        f0 = f1;
        f1 = f2;
        f2 = f;
        p2 += f2 * q;
        q *= x;
    }
    return p2;
}
int P2_ASM(int f0, int f1, int f2, int n, int x) {
    __asm {
        mov ebx, 1
        xor eax, eax
        cmp n, 0
        jl s
        mov ecx, f0
        imul ecx, ebx
        add eax, ecx
        imul ebx, x
        s :
        cmp n, 1
            jl s1
            mov ecx, f1
            imul ecx, ebx
            add eax, ecx
            imul ebx, x
            s1 :
        cmp n, 2
            jl s2
            mov ecx, f2
            imul ecx, ebx
            add eax, ecx
            imul ebx, x
            s2 :

        cmp n, 2
            jle s3
            c :
        mov ecx, 3
            imul ecx, f2
            imul ecx, f1
            mov edx, 4
            imul edx, f0
            sub ecx, edx

            mov edx, f1
            mov f0, edx
            mov edx, f2
            mov f1, edx
            mov f2, ecx

            imul ecx, ebx
            imul ebx, x

            add eax, ecx

            sub n, 1
            cmp n, 2
            jne c

            s3 :
    }
}

int main() {

    // задание 5 
    // f(n) = 3f(n-1)f(n-2) - 4f(n-3), n>=3
    
    int f0, f1, f2; 
    std::cout << "enter f0, f1, f2:\n";
    std::cin >> f0 >> f1 >> f2;
    int n, x;
    std::cout << "enter n, x\n";
    std::cin >> n >> x; 

    std::cout << "C++ P1 = " << P1(f0, f1, f2, n, x);
    std::cout << "\nASM P1 = " << P1_ASM(f0, f1, f2, n, x);
    std::cout << "\nC++ P2 = " << P2(f0, f1, f2, n, x);
    std::cout << "\nASM P2 = " << P2_ASM(f0, f1, f2, n, x);
}