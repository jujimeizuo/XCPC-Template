
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = acos(-1);
const int N = 3e5 + 10;
ll mod;

struct Complex {
    double x, y;
    Complex(double a = 0, double b = 0): x(a), y(b) {}
    Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
    Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
    Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Complex conj() { return Complex(x, -y); }
} w[N];

int tr[N];
ll F[N], G[N], D[N], R[N];

ll quick_pow(ll a, ll b) ;

int getLen(int n) ;

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

void Get_Inv(ll *f, ll *g, int n) ;

void rever(ll *f, int n) { for(int i = 0, j = n - 1;i < j; i++, j--) swap(f[i], f[j]); }

void Get_Div(ll *f, ll *g, ll *d, ll *r, int n, int m) {
    static ll a[N], b[N], invb[N];
    for(int i = 0;i < n; i++) a[i] = f[i];
    for(int i = 0;i < m; i++) b[i] = g[i];
    rever(a, n); rever(b, m);
    //for(int i = 0;i < n - m + 1; i++) b[i] = i < m ? b[i] : 0;
    Get_Inv(b, invb, n - m + 1);

    int len = getLen(n);
    MTT(a, invb, a, len);
    rever(a, n - m + 1);
    for(int i = 0;i < len; i++) d[i] = i < n - m + 1 ? a[i] : 0;
    MTT(g, d, b, len);
    for(int i = 0;i < m; i++) { r[i] = (f[i] - b[i] + mod) % mod; }

    for(int i = m;i < len; i++) r[i] = 0;
    for(int i = 0;i < len; i++) a[i] = b[i] = invb[i] = 0;
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0;i < n; i++) { cin >> F[i]; }
    for(int i = 0;i < m; i++) { cin >> G[i]; }
    Get_Div(F, G, D, R, n, m);

    for(int i = 0;i < n - m + 1; i++) cout << D[i] << " ";
    cout << endl;
    for(int i = 0;i < m - 1; i++) cout << R[i] << " ";
    cout << endl;
}
