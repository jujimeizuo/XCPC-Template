//将多项式拆成(a1 * mod + a2) * (b1 * mod + b2)的形式
//=>a1 * b1 * mod ^ 2 + (a2 * b1 + a1 * b2) * mod + a2 * b2
//在利用DFT合并、IDFT合并，最终只需要4次DFT即可
//精度10^14
//4倍空间

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

int tr[N];
ll a[N], b[N], ans[N];

int getLen(int n) {
    int len = 1; while (len <= n) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++) w[i] = w[i] = Complex(cos(2 * PI * i / len), sin(2 * PI * i / len));
    return len;
}

void FFT(Complex *A, int len) {
    for (int i = 0; i < len; i++) if(i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2, lyc = len >> 1; i <= len; i <<= 1, lyc >>= 1)
        for (int j = 0; j < len; j += i) {
            Complex *l = A + j, *r = A + j + (i >> 1), *p = w;
            for (int k = 0; k < i >> 1; k++) {
                Complex tmp = *r * *p;
                *r = *l - tmp, *l = *l + tmp;
                ++l, ++r, p += lyc;
            }
        }
}

inline void MTT(ll *x, ll *y, ll *z, int len) {
    for (int i = 0; i < len; i++) (x[i] += mod) %= mod, (y[i] += mod) %= mod;
    static Complex a[N], b[N];
    static Complex dfta[N], dftb[N], dftc[N], dftd[N];

    for (int i = 0; i < len; i++) a[i] = Complex(x[i] & 32767, x[i] >> 15);
    for (int i = 0; i < len; i++) b[i] = Complex(y[i] & 32767, y[i] >> 15);
    FFT(a, len), FFT(b, len);
    for (int i = 0; i < len; i++) {
        int j = (len - i) & (len - 1);
        static Complex da, db, dc, dd;
        da = (a[i] + a[j].conj()) * Complex(0.5, 0);
        db = (a[i] - a[j].conj()) * Complex(0, -0.5);
        dc = (b[i] + b[j].conj()) * Complex(0.5, 0);
        dd = (b[i] - b[j].conj()) * Complex(0, -0.5);
        dfta[j] = da * dc;
        dftb[j] = da * dd;
        dftc[j] = db * dc;
        dftd[j] = db * dd;
    }
    for (int i = 0; i < len; i++) a[i] = dfta[i] + dftb[i] * Complex(0, 1);
    for (int i = 0; i < len; i++) b[i] = dftc[i] + dftd[i] * Complex(0, 1);
    FFT(a, len), FFT(b, len);
    for (int i = 0; i < len; i++) {
        ll da = (ll)(a[i].x / len + 0.5) % mod;
        ll db = (ll)(a[i].y / len + 0.5) % mod;
        ll dc = (ll)(b[i].x / len + 0.5) % mod;
        ll dd = (ll)(b[i].y / len + 0.5) % mod;
        z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
    }
}

int main() {

    int n, m;
    scanf("%d%d%lld", &n, &m, &mod);
    for (int i = 0; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 0; i <= m; i++) scanf("%d", &b[i]);

    MTT(a, b, ans, n + m);
    for (int i = 0; i <= n + m; i++)
        printf("%s%d", i == 0 ? "" : " ", (ans[i] + mod) % mod);

    return 0;
}