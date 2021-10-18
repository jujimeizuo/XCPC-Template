// p不为质数，利用中国剩余定理结合求解
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

ll quick_pow(ll a, ll b, ll P) {
    ll ans = 1;
    while(b) {
        if(b & 1)
            ans = ans * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return ans % P;
}

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    ll res, t;
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    res = ex_gcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - (a / b) * y;
    return res;
}

ll INV(ll a, ll mod) {
    ll x, y;
    ll d = ex_gcd(a, mod, x, y);
    return d ? (x % mod + mod) % mod : -1;
}

ll fac(ll n, ll P, ll pk) {// 阶乘除去质因子后模质数幂 (n / p^a) % pk
    if(!n) return 1;
    ll ans = 1;
    for(int i = 1;i < pk; i++) {// 第三部分：n!与p互质的乘积
        if(i % P)
            ans = ans * i % pk;
    }
    ans = quick_pow(ans, n / pk, pk) % pk; // 第三部分：n!与p互质的乘积,ans循环的次数为n/pk
    for(int i = 1;i <= n % pk; i++) {// 第四部分：循环过后n!剩下的部分
        if(i % P) ans = ans * i % pk;
    }
    return ans * fac(n / P, P, pk) % pk;  // 第一部分，p的幂，个数为n/p；  第二部分：(n/p)!
}

ll C(ll m, ll n, ll P, ll pk) {// 组合数模质数幂
    if(n < 0 || m < 0 || n > m) return 0;
    ll f1 = fac(m, P, pk), f2 = fac(n, P, pk), f3 = fac(m - n, P, pk), tmp = 0; // tmp = pk1 - pk2 - pk3
    for(ll i = m; i ; i /= P)     tmp += i / P;
    for(ll i = n; i ; i /= P)     tmp -= i / P;
    for(ll i = m - n; i ; i /= P) tmp -= i / P;
    return f1 * INV(f2, pk) % pk * INV(f3, pk) * quick_pow(P, tmp, pk) % pk;
}

ll p[N], a[N];
int cnt;

ll CRT() {
    ll M = 1, ans = 0;
    for(int i = 1;i <= cnt; i++)  M *= p[i];
    for(int i = 1;i <= cnt; i++) {
        ll m = M / p[i];
        ans = (ans + a[i] * m % M * INV(m, p[i]) % M) % M;
    }
    return (ans % M + M) % M;
}

ll EX_Lucas(ll m, ll n, ll P) {
    for(int i = 2;i * i <= P; i++) {
        if(P % i == 0) {
            ll tmp = 1;
            while(P % i == 0) {
                tmp *= i;
                P /= i;
            }
            p[++cnt] = tmp;
            a[cnt] = C(m, n, i, tmp);
        }
    }
    if(P > 1) {
        p[++cnt] = P;
        a[cnt] = C(m, n, P, P);
    }
    return CRT();
}
int main() {
    ll m, n, P;
    cin >> m >> n >> P;
    cnt = 0;
    cout << EX_Lucas(m, n, P) << endl;
}