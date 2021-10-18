#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = acos(-1);
const int N = 1e5 + 10;

struct Complex {
    double x, y;
    Complex(double a = 0, double b = 0): x(a), y(b) {}
    Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
    Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
    Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Complex conj() { return Complex(x, -y); }
} w[N];

ll mod, inv2;
int tr[N];
ll F[N], G[N];

ll quick_pow(ll a, ll b) ;

int getLen(int n) ;

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

void Get_Inv(ll *f, ll *g, int n) ;

void Get_Der(ll *f, ll *g, int len) { for(int i = 1;i < len; i++) g[i - 1] = f[i] * i % mod; g[len - 1] = 0; }

void Get_Int(ll *f, ll *g, int len) { for(int i = 1;i < len; i++) g[i] = f[i - 1] * quick_pow(i, mod - 2) % mod; g[0] = 0; }

void Get_Ln(ll *f, ll *g, int n) ;

void Get_Exp(ll *f, ll *g, int n) ;

void Get_Pow(ll *f, ll *g, int n, ll k) ;

void Get_Sqrt(ll *f, ll *g, int n) {
    static ll a[N];
    Get_Ln(f, a, n);
    for(int i = 0;i < n; i++) a[i] = a[i] * inv2 % mod;
    Get_Exp(a, g, n);
    int len = getLen(n);
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) a[i] = 0;
}

