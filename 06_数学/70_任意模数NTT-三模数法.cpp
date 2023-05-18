//要求选取的三个模数mod1 * mod2 * mod3 >= p^2*n
//优点是精度高，可达10^26
//缺点是常数大(9次NTT)，并且还使用了龟速乘
//4倍空间

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 4e5 + 10;

ll qmul(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = qmul(res, a, mod);
        a = qmul(a, a, mod);
        b >>= 1;
    }
    return res;
}

const ll mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, mod4 = mod1 * mod2;
const ll G = 3;
ll a[3][MAX], b[3][MAX], ans[MAX], p;
int tr[MAX];

void NTT(ll *A, int len, int type, ll mod) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        int mid = i / 2;
        ll Wn = qpow(type == 1 ? G : qpow(G, mod - 2, mod), (mod - 1) / i, mod);
        for (int k = 0; k < len; k += i) {
            ll w = 1;
            for (int l = k; l < k + mid; l++) {
                ll t = w * A[l + mid] % mod;
                A[l + mid] = (A[l] - t + mod) % mod;
                A[l] = (A[l] + t) % mod;
                w = w * Wn % mod;
            }
        }
    }
    if (type != 1) {
        ll invn = qpow(len, mod - 2, mod);
        for (int i = 0; i < len; i++) A[i] = A[i] * invn % mod;
    }
}

void mul(int i, int len, ll mod) {
    NTT(a[i], len, 1, mod), NTT(b[i], len, 1, mod);
    for (int j = 0; j < len; j++) a[i][j] = a[i][j] * b[i][j] % mod;
    NTT(a[i], len, -1, mod);
}

void CRT(int len) {
    ll inv1 = qpow(mod2, mod1 - 2, mod1);
    ll inv2 = qpow(mod1, mod2 - 2, mod2);
    ll inv3 = qpow(mod4 % mod3, mod3 - 2, mod3);
    for (int i = 0; i < len; i++) {
        ll t = 0;
        t = (t + qmul(a[0][i] * mod2 % mod4, inv1, mod4)) % mod4;
        t = (t + qmul(a[1][i] * mod1 % mod4, inv2, mod4)) % mod4;
        a[1][i] = t;
        t = (a[2][i] - a[1][i] % mod3 + mod3) % mod3 * inv3 % mod3;
        ans[i] = (mod4 % p * t % p + a[1][i] % p) % p;
    }
}

void doNTT(int n) {
    int len = 1; while (len <= n) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    mul(0, len, mod1), mul(1, len, mod2), mul(2, len, mod3);
    CRT(len);
}

int main() {

    int n, m;
    scanf("%d%d%lld", &n, &m, &p);
    for (int i = 0; i <= n; i++) {
        ll x; scanf("%lld", &x);
        a[0][i] = a[1][i] = a[2][i] = x % p;
    }
    for (int i = 0; i <= m; i++) {
        ll x; scanf("%lld", &x);
        b[0][i] = b[1][i] = b[2][i] = x % p;
    }
    doNTT(n + m);
    for (int i = 0; i <= n + m; i++) printf("%lld ", ans[i]);

    return 0;
}