#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

const int N = 1e5 + 10;
int a[N], b[N];

inline void FWT_OR(int *f, int n, int opt) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
                f[i + j + k] = (f[i + j + k] + 1ll * f[i + j] * opt % mod + mod) % mod;
}

inline void FWT_AND(int *f, int n, int opt) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
                f[i + j] = (f[i + j] + 1ll * f[i + j + k] * opt % mod + mod) % mod;
}

inline void FWT_XOR(int *f, int n, int opt) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++) {
                ll a0 = f[i + j], a1 = f[i + j + k];
                f[i + j] = (a0 + a1) % mod * opt % mod;
                f[i + j + k] = (a0 - a1 + mod) % mod * opt % mod;
            }
}

inline void mul_OR(int *a, int *b, int n) {
    FWT_OR(a, n, 1); FWT_OR(b, n, 1);
    for(int i = 0;i < n; i++) a[i] = a[i] * b[i] % mod;
    FWT_OR(a, n, -1);
}

inline void mul_AND(int *a, int *b, int n) {
    FWT_AND(a, n, 1); FWT_AND(b, n, 1);
    for(int i = 0;i < n; i++) a[i] = a[i] * b[i] % mod;
    FWT_AND(a, n, -1);
}

ll quick_pow(ll a, ll b) ;

inline void mul_XOR(int *a, int *b, int n) {
    ll inv2 = quick_pow(mod, mod - 2);
    FWT_XOR(a, n, 1); FWT_XOR(b, n, 1);
    for(int i = 0;i < n; i++) a[i] = a[i] * b[i] % mod;
    FWT_XOR(a, n, inv2);
}

int main() {
    int n;
    cin >> n;
    n = 1 << n;
    for(int i = 0;i < n; i++) cin >> a[i];
    for(int i = 0;i < n; i++) cin >> b[i];
    
    mul_OR(a, b, n);
    mul_AND(a, b, n);
    mul_XOR(a, b, n);


}