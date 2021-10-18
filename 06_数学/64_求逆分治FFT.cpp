// f[i] = \sum_{j=1}^i f[i-j] * g[j]
// g相同，可以用多项式求逆
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

int getLen(int n) ;

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

void Get_Inv(ll *f, ll *g, int n) ;

void fenzhiFFT(ll *f, ll *g, int n) {
    static ll a[N];
    for(int i = 1;i < n; i++) a[i] = (mod - f[i]) % mod;
    a[0] = 1;
    Get_Inv(a, g, n);

    for(int i = 0;i < n; i++) {
        a[i] = 0;
    }
}

int main() {
    int n;
    cin >> n;
    for(int i = 1;i < n; i++) cin >> G[i];
    fenzhiFFT(G, F, n);
    
    for(int i = 0;i < n; i++) cout << F[i] << " ";
}