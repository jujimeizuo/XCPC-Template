#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;

// P[x] = \sum_{i=0}^{m-1} A[i] + \sum_{i=0}^{m-1} B[x - m + i + 1] - 2 * \sum_{i=0}^{m-1}A[i] * B[x - m + i + 1]

// reverse(a)

// 当串中的字符集较少时，可以针对每个字符进行FFT，计算每个字符对整个串的贡献

ll qpow(ll a, ll b, ll mod) ;

const ll mod = 998244353;
const ll G = 3;
const ll invG = qpow(G, mod - 2, mod);
int tr[N];

void NTT(ll *A, int len, int type) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        int mid = i / 2;
        ll Wn = qpow(type == 1 ? G : invG, (mod - 1) / i, mod);
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
    if (type == -1) {
        ll invn = qpow(len, mod - 2, mod);
        for (int i = 0; i < len; i++)
            A[i] = A[i] * invn % mod;
    }
}

void mul(ll *a, ll *b, int n) {
    int len = 1; while (len <= n) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
}

ll a[N], b[N];

void solve() {
    string s, t; cin >> s >> t;
    int n = s.length(), m = t.length();
    for(int i = 0;i < n; i++) a[i] = s[i] - 'a' + 1;
    for(int i = 0;i < m; i++) b[i] = t[i] - 'a' + 1;
    reverse(b, b + m);
    mul(a, b, n + m - 2);
    double P = 0;
    for(int i = 0;i < m; i++) {
        P += (t[i] - 'a' + 1) * (t[i] - 'a' + 1);
    }
    vector<int> f(n + 1);
    for(int i = 1;i < n; i++) {
        f[i] = f[i - 1] + (s[i] - 'a' + 1) * (s[i] - 'a' + 1);
    }
    for(int x = m - 1;x < n; x++) {
        double res;
        if(x == m - 1) res = P + f[x] - a[x] * 2;
        else res = P + f[x] - f[x - m] - a[x] * 2;
        if(!res) cout << x - m + 2 << endl;
    }
}