
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 20;

ll S2[N][N];
ll B[N];

void Stirling2() {
    S2[0][0] = 1;
    
    for(int i = 1;i < N; i++) {
        for(int j = 1;j <= i; j++) {
            S2[i][j] = S2[i - 1][j - 1] + j * S2[i - 1][j];
        }
    } 

}

// 根据第二类斯特林数

void Bell1() {
    
    for(int i = 0;i < N; i++) {
        for(int j = 0;j <= i; j++) {
            B[i] += S2[i][j];
        }
    }
}

// Bell三角形递推

ll b[N][N];

void Bell2() {
    b[1][1] = 1;
    for(int i = 2;i < N; i++) {
        b[i][1] = b[i - 1][i - 1];
        
        for(int j = 2;j < N; j++) {
            b[i][j] = b[i][j - 1] + b[i - 1][j - 1];
        }
    }
}

// 自身递推

ll fac[N];

ll C(ll m, ll n) {
    return fac[m] / (fac[n] * fac[m - n]);
}

void Bell3() {

    fac[1] = 1;
    for(int i = 2;i < N; i++)
        fac[i] = fac[i - 1] * i;

    B[0] = 1;

    for(int i = 1;i < N; i++) {
        for(int k = 0;k <= i; k++) {
            B[i] += C(i, k) * B[k];
        }
    }
}

