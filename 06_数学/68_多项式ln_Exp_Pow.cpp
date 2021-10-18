#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = acos(-1);

const int N = 1e6 + 10;

ll quick_pow(ll a, ll b) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

const ll G = 3;
const ll invG = quick_pow(G, mod - 2);

int tr[N];
bool flag;

void NTT(ll *A, int len, int type) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        int mid = i / 2;
        ll Wn = quick_pow(type == 1 ? G : invG, (mod - 1) / i);
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
        ll invn = quick_pow(len, mod - 2);
        for (int i = 0; i < len; i++)
            A[i] = A[i] * invn % mod;
    }
}

void mul(ll *a, ll *b, int len) {
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1); NTT(b, len, -1);
}

int getLen(int n) {
    int len = 1; while (len <= (n << 1)) len <<= 1;
    return len;
}

void Get_Der(ll *f, ll *g, int len) { for(int i = 1;i < len; i++) g[i - 1] = f[i] * i % mod; g[len - 1] = 0; }

void Get_Int(ll *f, ll *g, int len) { for(int i = 1;i < len; i++) g[i] = f[i - 1] * quick_pow(i, mod - 2) % mod; g[0] = 0; }

void Get_Inv(ll *f, ll *g, int n) {
    if(n == 1) { g[0] = quick_pow(f[0], mod - 2); return ; }
    Get_Inv(f, g, (n + 1) >> 1);

    int len = getLen(n);
    static ll c[N];
    for(int i = 0;i < len; i++) c[i] = i < n ? f[i] : 0;
    mul(c, g, len);
    mul(c, g, len);
    for(int i = 0;i < n; i++) g[i] = (2ll * g[i] - c[i] + mod) % mod;
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) c[i] = 0;
}

void Get_Ln(ll *f, ll *g, int n) {
    static ll a[N], b[N];
    Get_Der(f, a, n);
    Get_Inv(f, b, n);
    int len = getLen(n);
    mul(a, b, len);
    Get_Int(a, g, len);
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) a[i] = b[i] = 0;
}

void Get_Exp(ll *f, ll *g, int n) {
    if(n == 1) return (void)(g[0] = 1);
    Get_Exp(f, g, (n + 1) >> 1);

    static ll a[N];
    Get_Ln(g, a, n);
    a[0] = (f[0] + 1 - a[0] + mod) % mod;
    for(int i = 1;i < n; i++) a[i] = (f[i] - a[i] + mod) % mod;
    int len = getLen(n);
    mul(g, a, len);
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) a[i] = 0;
}

void Get_Pow(ll *f, ll *g, int n, ll k1, ll k2) {
    static ll a[N], b[N], c[N];
    ll deg = 0; for(int i = 0;i < n && f[i] == 0; i++) ++ deg;
    if(deg * k1 > n || (flag && deg)) return ;
    ll f0 = f[deg], f0k = quick_pow(f0, k2), inv0 = quick_pow(f0, mod - 2);
    for(int i = deg;i < n; i++) a[i - deg] = f[i] * inv0 % mod;
    Get_Ln(a, b, n);
    for(int i = 0;i < n - deg * k1; i++) b[i] = b[i] * k1 % mod;
    Get_Exp(b, c, n);
    deg *= k1;
    for(int i = deg;i < n; i++) g[i] = (c[i - deg] * f0k % mod + mod) % mod;
    for(int i = 0;i < deg; i++) g[i] = 0;
    int len = getLen(n);
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) a[i] = b[i] = c[i] = 0;
}


ll a[N], ans[N];

void solve() {
    int n; string s; cin >> n >> s;
    ll k1 = 0, k2 = 0;
    for(int i = 0; i < s.length(); i++) {
        k1 = (k1 * 10 + s[i] - '0');
        flag |= (k1 >= mod);
        k1 %= mod;
        k2 = (k2 * 10 + s[i] - '0') % (mod - 1);
    }
    for(int i = 0; i < n; i++) cin >> a[i];
    Get_Pow(a, ans, n, k1, k2); // k1是底 % mod，k2是指数 % mod-1
    for(int i = 0;i < n; i++) cout << ans[i] << (i == n - 1 ? endl : " ");
}