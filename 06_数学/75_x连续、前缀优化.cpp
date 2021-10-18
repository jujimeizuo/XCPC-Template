
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

ll mod;
ll F[N];
ll pre[N], suf[N];
ll fac[N], invf[N];


ll quick_pow(ll a, ll b) ;

void init() {
    fac[0] = 1;
    for(int i = 1;i < N; i++) fac[i] = fac[i - 1] * i % mod;
    invf[N - 1] = quick_pow(fac[N - 1], mod - 2);
    for(int i = N - 1;i >= 1; i--) invf[i - 1] = invf[i] * i % mod;
}

ll Lagrange(ll *f, int k, int n) {
    if(k <= n) return f[k]; 
    pre[0] = suf[n] = 1;
    for(int i = 1;i <= n; i++) pre[i] = pre[i - 1] * (k - i + 1) % mod;
    for(int i = n;i >= 1; i--) suf[i - 1] = suf[i] * (k - i) % mod;
    ll ans = 0;
    for(int i = 0;i <= n; i++) {
        int opt = (n - i) & 1 ? -1 : 1;
        ans = (ans + 1ll * opt * pre[i] % mod * suf[i] % mod * invf[i] % mod * invf[n - i] % mod * f[i] % mod + mod) % mod;
    }
    return f[k] = ans;
}

int main() {
    init();
    int n, k;
    cin >> n >> k;
    for(int i = 0;i <= n; i++) cin >> F[i];
    cout << Lagrange(F, k, n) << endl;

}