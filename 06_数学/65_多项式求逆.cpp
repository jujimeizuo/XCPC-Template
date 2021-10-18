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

ll mod;
int tr[N];
ll F[N], G[N];

ll quick_pow(ll a, ll b) ;

int getLen(int n) {
    int len = 1; while (len < (n << 1)) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++) w[i] = w[i] = Complex(cos(2 * PI * i / len), sin(2 * PI * i / len));
    return len;
}

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

void Get_Inv(ll *f, ll *g, int n) {
    if(n == 1) { g[0] = quick_pow(f[0], mod - 2); return ; }
    Get_Inv(f, g, (n + 1) >> 1);

    int len = getLen(n);
    static ll c[N];
    for(int i = 0;i < len; i++) c[i] = i < n ? f[i] : 0;
    MTT(c, g, c, len); MTT(c, g, c, len);
    for(int i = 0;i < n; i++) g[i] = (2ll * g[i] - c[i] + mod) % mod;
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) c[i] = 0;
}

int main() {
    int n;
    cin >> n;
    for(int i = 0;i < n; i++) cin >> F[i];
    Get_Inv(F, G, n);
    for(int i = 0;i < n; i++) cout << G[i] << " ";
}
