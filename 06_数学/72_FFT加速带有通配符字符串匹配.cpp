#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// p[x] = \sum_{i=0}^{m-1} A[i]^3 * B[x-m+i+1] + \sum_{i=0}^{m-1} A[i] * B[x-m+i+1]^3 - 2 * \sum_{i=0}^{m-1} A[i]^2 * B[x-m+i+1]^2

const int N = 1e6 + 1e5;

ll qpow(ll a, ll b, ll mod) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

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

ll a1[N], a2[N], a3[N], b1[N], b2[N], b3[N];

void solve() {
    int m, n; cin >> m >> n;
    string s, t; cin >> t >> s;
    for(int i = 0;i < m; i++) {
        if(t[i] == '*') continue ;
        int temp = t[i] - 'a' + 1;
        a1[i] = temp;
        a2[i] = temp * temp;
        a3[i] = temp * temp * temp;
    }
    for(int i = 0;i < n; i++) {
        if(s[i] == '*') continue;
        int temp = s[i] - 'a' + 1;
        b1[i] = temp;
        b2[i] = temp * temp;
        b3[i] = temp * temp * temp;
    }
    reverse(a1, a1 + m);
    reverse(a2, a2 + m);
    reverse(a3, a3 + m);
    mul(a1, b3, n + m);
    mul(a2, b2, n + m);
    mul(a3, b1, n + m);
    vector<int> ans;
    for(int x = m - 1;x < n; x++) {
        ll res = a1[x] + a3[x] - a2[x] * 2;
        if(!res) ans.push_back(x - m + 2);
    }
    cout << ans.size() << endl;
    for(int i = 0;i < ans.size(); i++) cout << ans[i] << (i == ans.size() - 1 ? endl : " ");
}