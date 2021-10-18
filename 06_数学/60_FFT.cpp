#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1);
const int N = 4e5 + 10;

struct Complex {
    double a, b;
    Complex(double a = 0, double b = 0): a(a), b(b) {}
    Complex operator * (const Complex &rhs) { return Complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    Complex operator + (const Complex &rhs) { return Complex(a + rhs.a, b + rhs.b); }
    Complex operator - (const Complex &rhs) { return Complex(a - rhs.a, b - rhs.b); }
};

int tr[N];

void FFT(Complex *A, int len, int type) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {//区间长度
        int mid = i / 2;
        Complex Wn(cos(2 * PI / i), type * sin(2 * PI / i));//单位根
        for (int k = 0; k < len; k += i) {//每个子问题的起始点
            Complex w(1, 0);//omega
            for (int l = k; l < k + mid; l++) {
                Complex t = w * A[l + mid];
                A[l + mid] = A[l] - t;
                A[l] = A[l] + t;
                w = w * Wn;
            }
        }
    }
}

void mul(ll *x, int n, ll *y, int m) {
    static Complex a[N], b[N];
    for(int i = 0;i <= n; i++) a[i].a = x[i];
    for(int i = 0;i <= m; i++) b[i].a = y[i];
    int len = 1; while (len <= (n + m)) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    FFT(a, len, 1), FFT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i];
    FFT(a, len, -1);
    for (int i = 0; i < len; i++) x[i] = (ll)(a[i].a / len + 0.5);
}

ll a[N], b[N];

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i <= m; i++) scanf("%lld", &b[i]);

    mul(a, n, b, m);
    for (int i = 0; i <= n + m; i++)
        printf("%lld ", a[i]);
}