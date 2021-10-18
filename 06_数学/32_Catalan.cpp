
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int C[N];

// 线性递推

void Calc1() {
    C[0] = 1;
    for(int i = 1;i < N; i++) {
        C[i] = C[i - 1] * (4 * i - 2) / (i + 1);
    }
}

// 组合数求解 

int f[N];

void fac() {
    f[0] = 1;
    for(int i = 1;i < N; i++) {
        f[i] = f[i - 1] * i;
    }
}

void Calc2(int n) {
    C[n] = f[2 * n] / f[n + 1];
}

// 多项式求解

void Calc3(int n) {
    if(n == 1)
        C[n] = 1;
    
    for(int i = 1;i <= n; i++) {
        C[n] += C[n - i] * C[i - 1];
    }
}