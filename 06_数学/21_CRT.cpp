#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll m[10005], a[10005], n; //a是余数，b是模数

void exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b , y , x);
    y -= a / b * x;
}

ll INV(ll a, ll mod) {
    ll x, y;
    exgcd(a , mod , x , y);
    x = (x % mod + mod) % mod;
    return x;
}

ll CRT() {
    ll ans = 0, M = 1;
    for(ll i = 1;i <= n; i++) {
        M *= m[i]; // M是所有除数的乘积
    }
    for(ll i = 1;i <= n; i++) {
        ll mm = M / m[i];
        ll ret = INV(mm , m[i]); // 先求逆元
        ans = (ans + a[i] * mm % M * ret % M) % M;
/*
ans = (ans + quick_mul(quick_mul(m , ret , M) , b[i] , M)) % M;
利用快速乘防止爆longlong 
*/
    }
    return (ans + M) % M;
}

int main() {
    ll ans = 0;
    scanf("%lld",&n);
    for(ll i = 1;i <= n; i++) {
        scanf("%lld%lld",&m[i],&a[i]);
        a[i] = (a[i] % m[i] + m[i]) % m[i];// 防止b[i]为负
    }
    ans = CRT(); // 精髓
    printf("%lld",ans);
    return 0;
}