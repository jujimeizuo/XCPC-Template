#include "bits/stdc++.h"
using namespace std;

const int N = 2e6 + 10;

const int P = 998244353, g3 = (P + 1) / 3;

int pow(int a,int b) {
    int r = 1;
    while(b) {
        if(b & 1) r = (ll)r * a % P;
        a = (ll)a * a % P;
        b >>= 1;
    }
    return r;
}
namespace poly {
    int rev[N];
    void NTT(int *A, int n, int inv) {
        for(int i = 0; i < n; ++i)
            if(i < rev[i]) swap(A[i], A[rev[i]]);
        for(int mid = 1; mid < n; mid <<= 1) {
            int tmp = pow(inv == 1 ? 3 : g3, (P - 1) / (mid << 1));
            for(int j = 0; j < n; j += (mid << 1)) {
                int omega = 1;
                for(int k = 0; k < mid; ++k, omega = (ll)omega * tmp % P) {
                    int x = A[j + k], y = (ll)omega * A[j + k + mid] % P;
                    A[j + k] = (x + y) % P;
                    A[j + k + mid] = (ll)(x - y + P) % P;
                }
            }
        }
        if(inv == 1) return;
        int invn = pow(n, P - 2);
        for(int i = 0; i < n; ++i)
            A[i] = (ll)A[i] * invn % P;
    }
    void Inv(int *a, int *b, int n) {
        static int B[N], A[N];
        b[0] = pow(a[0], P - 2);
        int len, lim;
        for(len = 1; len < (n << 1); len <<= 1) {
            lim = len << 1;
            for(int i = 0; i < len; i++)
                A[i] = a[i], B[i] = b[i];
            for(int i = 0; i < lim; i++)
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? len : 0);
            NTT(A, lim, 1), NTT(B, lim, 1);
            for(int i = 0; i < lim; i++)
                b[i] = ((2LL - 1LL * A[i] * B[i] % P) * B[i] % P + P) % P;
            NTT(b, lim, -1);
            for(int i = len; i < lim; i++)
                b[i] = 0;
        }
        for(int i = 0; i < len; i++)
            A[i] = B[i] = 0;
        for(int i = n; i < len; i++)
            b[i] = 0;
    }
    void derivative(int *a, int *b, int n) {
        b[n - 1] = 0;
        for(int i = 1; i < n; ++i)
            b[i - 1] = (ll)a[i] * i % P;
    }
    void inter(int *a, int *b, int n) {
        *b = 0;
        for(int i = n - 1; i >= 0; --i)
            b[i + 1] = a[i] * (ll)pow(i + 1, P - 2) % P;
    }
    void ln(int *a, int *b, int n) {
        static int F[N];
        derivative(a, F, n);
        Inv(a, b, n);
        int lim = 1;
        while(lim < (n << 1)) lim <<= 1;
        for(int i = 1; i < lim; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
        for(int i = n; i < lim; ++i)
            b[i] = F[i] = 0;
        NTT(F, lim, 1), NTT(b, lim, 1);
        for(int i = 0; i < lim; ++i)
            F[i] = (ll)b[i] * F[i] % P;
        NTT(F, lim, 0);
        inter(F, b, n);
        for(int i = n; i < lim; ++i)
            b[i] = 0;
    }
    void exp(int*a, int*F, int n) {
        if(n == 1)
            *F = 1;
        else {
            exp(a, F, n + 1 >> 1);
            static int F0[N], A[N];
            for(int i = 0; i <= (n << 1); ++i)
                F0[i] = 0, A[i] = a[i];
            ln(F, F0, n);
            int lim = 1;
            while(lim < (n << 1)) lim <<= 1;
            for(int i = 1; i < lim; i++)
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
            for(int i = n; i < lim; ++i)
                A[i] = 0;
            NTT(A, lim, 1), NTT(F0, lim, 1), NTT(F, lim, 1);
            for(int i = 0; i < lim; ++i)
                F[i] = F[i] * (A[i] + 1LL - F0[i] + P) % P;
            NTT(F, lim, 0);
            for(int i = n; i < lim; ++i)
                F[i] = 0;
        }
    }
}
using namespace poly;

int a[N], b[N];

void solve() {
  int n, m, k; cin >> n >> m >> k;
  for(int i = 0;i < n; i++) cin >> a[i];
  ln(a, b, m);
  for(int i = 0;i < m; i++) b[i] = b[i] * k % mod;
  exp(b, a, m);
  for(int i = 0;i < m; i++) cout << a[i] << " ";
}
