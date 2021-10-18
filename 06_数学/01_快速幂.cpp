#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll quick_pow(ll a, ll b, ll mod) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

// 快速乘和中国剩余定理搭配更香哦
ll ksc(ll a, ll b, ll mod)   {
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

ll quick_mul(ll a,ll b,ll c) {
    return (a * b - (ll)((ld)a * b / c) * c + c) % c;
}


const int N = 100 + 10;

int n;

struct Martix {
    ll a[N][N];
    Martix operator * (const Martix &rhs) const {
        Martix ans;
        mem(ans.a, 0);
        for(int i = 1;i <= n; i++) {
            for(int j = 1;j <= n; j++) {
                for(int k = 1;k <= n; k++) {
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * rhs.a[k][j]) % mod;
                }
            }
        }
        return ans;
    }
};

Martix quick_pow(Martix a, ll b) {
    Martix ans; mem(ans.a, 0);
    for(int i = 1;i <= n; i++) ans.a[i][i] = 1;
    while(b) {
        if(b & 1) ans = a * ans;
        a = a * a;
        b >>= 1;
    }
    return ans;
}