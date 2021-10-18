// 模数非质数情况下的组合问题
// one way, use CRT merge ans
// https://ac.nowcoder.com/discuss/655940?type=101&order=0&pos=2&page=1&channel=-1&source_id=discuss_tag_nctrack
// another way
// https://ac.nowcoder.com/acm/contest/view-submission?submissionId=47754622

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll res = exgcd(b, a % b, x, y);
    ll t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

ll inv(ll a, ll b) {
    ll x = 0, y = 0;
    exgcd(a, b, x, y);
    return x = (x % b + b) % b;
}

//r[]为余数, m为模数, 其中模数互质
//M = pi(mi), Mi = M / mi, invMi = Mi % mi
//ni满足是除了mi之外的倍数, 且模mi为ri
//利用逆元性质, 即ri * Mi * invMi = ri (mod mi)
//res = (sigma(ri * Mi * invMi)) % M

ll china(ll r[], ll m[], int n) {
    ll M = 1, res = 0;
    for (int i = 1; i <= n; i++) M *= m[i];
    for (int i = 1; i <= n; i++) {
        ll Mi = M / m[i], invMi = inv(Mi, m[i]);
        res = (res + r[i] * Mi % M * invMi % M) % M;
        //res = (res + mul(mul(r[i], Mi, M), invMi, M)) % M;按位乘
    }
    return (res % M + M) % M;
}

int f[N], g[N], F[N], G[N], invF[N];

int calc(int n, int p, int k) {
    ll mod = qpow(p, k, LONG_LONG_MAX);
    F[0] = 1, G[0] = 0;
    for (int i = 1; i <= n; i++) {
        g[i] = 0, f[i] = i;
        while (f[i] % p == 0) f[i] /= p, g[i]++;
        F[i] = 1ll * F[i - 1] * f[i] % mod;
        G[i] = G[i - 1] + g[i];
    }
    invF[n] = inv(F[n], mod);
    for (int i = n; i >= 1; i--) invF[i - 1] = 1ll * invF[i] * f[i] % mod;
    int ans = 0;
    for (int i = 0; i <= n / 2; i++) {
        int t = 1ll * F[n] * invF[n - 2 * i] % mod * invF[i] % mod * invF[i] % mod *
                qpow(p, G[n] - G[n - 2 * i] - 2 * G[i], LONG_LONG_MAX) % mod;
        ans = (ans + 1ll * t) % mod;
    }
    return ans;
}

ll r[20], m[20];

int main() {
#ifdef ACM_LOCAL
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int n, p;
    scanf("%d%d", &n, &p);
    int num = 0;
    for (int i = 2; i * i <= p; i++)
        if (p % i == 0) {
            int k = 0;
            m[++num] = 1;
            while (p % i == 0) p /= i, k++, m[num] *= i;
            r[num] = calc(n, i, k);
        }
    if (p > 1) {
        m[++num] = p;
        r[num] = calc(n, p, 1);
    }
    printf("%lld\n", china(r, m, num));

    return 0;
}