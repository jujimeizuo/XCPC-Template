#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

//mod比最终答案要大
//如果中间乘法计算会爆ll, 换成按位乘
//精度高, 比3次FFT要快(复数运算=>整数运算)
//4倍空间

ll qpow(ll a, ll b, ll mod) ;

const ll mod = 998244353;
const ll G = 3;
const ll invG = qpow(G, mod - 2, mod);
int tr[N];

void NTT(ll *A, int len, int type) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        int mid = i / 2;
        ll Wn = qpow(type == 1 ? G : invG, (mod - 1) / i, mod);
        for (int k = 0; k < len; k += i) {
            ll w = 1;
            for (int l = k; l < k + mid; l++) {
                ll t = w * A[l + mid] % mod;
                A[l + mid] = (A[l] - t + mod) % mod;
                A[l] = (A[l] + t) % mod;
                w = w * Wn % mod;
            }
        }
    }
    if (type == -1) {
        ll invn = qpow(len, mod - 2, mod);
        for (int i = 0; i < len; i++)
            A[i] = A[i] * invn % mod;
    }
}

void mul(ll *a, ll *b, int n) {
    int len = 1; while (len <= n) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
}

int n, m;
ll a[N], b[N];

int main() {

    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i <= m; i++) scanf("%lld", &b[i]);

    mul(a, b, n + m);
    for (int i = 0; i <= n + m; i++)
        printf("%lld ", a[i]);

    return 0;
}