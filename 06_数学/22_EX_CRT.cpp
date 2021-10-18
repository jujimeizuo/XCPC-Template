#include <iostream>

using namespace std;

typedef long long ll;

ll c[100005], m[100005], n; 

ll ksc(ll a, ll b, ll mod) {
    ll ans = 0;
    while(b > 0) {
        if(b & 1) {
            ans = (ans + a) % mod;
        }
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ans;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
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

ll EX_CRT() {
    ll x, y;
    ll ans = c[1];
    ll M = m[1];
    for(int i = 2; i <= n; i++) {
        ll C = ((c[i] - ans) % m[i] + m[i]) % m[i];
        ll T = ex_gcd(M, m[i], x, y);
        if((c[i] - ans) % T)
            return -1;
        x = ksc(x, C / T, m[i] / T);
        ans += M * x;
        M *= (m[i] / T);
        ans = (ans % M + M) % M;
    }
    return ans;
}

/*
ll EX_CRT() // 便于理解
{
    for(int i = 2;i <= n; i++)
    {
        ll M1 = m[i - 1], M2 = m[i], C1 = c[i - 1], C2 = c[i];
        ll T = gcd(M1, M2); // gcd(M1, M2)
        if((C2 - C1) % T) // 无解
            return -1;
        m[i] = (M1 * M2) / T; // 合并后新同余方程的模
        c[i] = INV(M1 / T, M2 / T) * (C2 - C1) / T % (M2 / T) * M1 + C1; // 可快速乘优化
        c[i] = (c[i] % m[i] + m[i]) % m[i]; // 合并后新同余方程的余
    }
    return c[n];
}
*/

int main()
{
    cin >> n;
    for(int i = 1;i <= n; i++)
    cin >> c[i] >> m[i];
    cout << EX_CRT() << endl;
}