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

// 矩阵快速幂

struct Matrix {
  ll m[3][3];

  void clear() { memset(m, 0, sizeof(m)); }
  void init()  { for(int i = 1;i <= 2; i++) m[i][i] = 1; }
  bool check() { return m[1][1] && !m[1][2] && !m[2][1] && m[2][2] ? 1 : 0; }

  Matrix operator * (const Matrix &a) {
    Matrix res; res.clear();
    for(int i = 1;i <= 2; i++) {
      for(int j = 1;j <= 2; j++) {
        for(int k = 1;k <= 2; k++) {
          (res.m[i][j] += a.m[i][k] * m[k][j]) %= mod; 
        }
      }  
    }
    return res;
  }

  Matrix operator + (const Matrix &a) {
    Matrix res; res.clear();
    for(int i = 1;i <= 2; i++) {
      for(int j = 1;j <= 2; j++) {
        res.m[i][j] = (a.m[i][j] + m[i][j]) % mod;
      }
    }
    return res;
  }
};

Matrix operator ^ (Matrix a, ll b) {
  Matrix ans;
  ans.clear(); ans.init();
  while(b) {
    if(b & 1) ans = ans * a;
    a = a * a;
    b >>= 1;
  }
  return ans;
}
