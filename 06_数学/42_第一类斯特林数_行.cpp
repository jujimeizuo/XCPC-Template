#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long LL;
const int N = 550050;
const int mod = 167772161;

LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}

int L, rev[N];
LL w[N], inv[N], fac[N], ifac[N];

void Init(int n) {
  L = 1;
  while (L <= n) L <<= 1;
  for (int i = 1; i < L; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * L / 2);
  LL wn = pow_mod(3, (mod - 1) / L);
  w[L >> 1] = 1;
  for (int i = L >> 1; i < L; ++i) w[i + 1] = w[i] * wn % mod;
  for (int i = (L >> 1) - 1; i; --i) w[i] = w[i << 1];
}

void DFT(LL *A, int len) {
  int k = __builtin_ctz(L) - __builtin_ctz(len);
  for (int i = 1; i < len; ++i) {
    int j = rev[i] >> k;
    if (j > i) std::swap(A[i], A[j]);
  }
  for (int h = 1; h < len; h <<= 1)
    for (int i = 0; i < len; i += (h << 1))
      for (int j = 0; j < h; ++j) {
        LL t = A[i + j + h] * w[j + h] % mod;
        A[i + j + h] = A[i + j] - t;
        A[i + j] += t;
      }
  for (int i = 0; i < len; ++i) A[i] %= mod;
}

void IDFT(LL *A, int len) {
  std::reverse(A + 1, A + len);
  DFT(A, len);
  int v = mod - (mod - 1) / len;
  for (int i = 0; i < len; ++i) A[i] = A[i] * v % mod;
}

void offset(const LL *f, int n, LL c, LL *g) {
  // g(x) = f(x + c)
  // g[i] = 1/i! sum_{j=i}^n j!f[j] c^(j-i)/(j-i)!
  static LL tA[N], tB[N];
  int l = 1; while (l <= n + n) l <<= 1;
  for (int i = 0; i < n; ++i) tA[n - i - 1] = f[i] * fac[i] % mod;
  LL pc = 1;
  for (int i = 0; i < n; ++i, pc = pc * c % mod) tB[i] = pc * ifac[i] % mod;
  for (int i = n; i < l; ++i) tA[i] = tB[i] = 0;
  DFT(tA, l); DFT(tB, l);
  for (int i = 0; i < l; ++i) tA[i] = tA[i] * tB[i] % mod;
  IDFT(tA, l);
  for (int i = 0; i < n; ++i)
    g[i] = tA[n - i - 1] * ifac[i] % mod;
}

void Solve(int n, LL *f) {
  if (n == 0) return void(f[0] = 1);
  static LL tA[N], tB[N];
  int m = n / 2;
  Solve(m, f);
  int l = 1; while (l <= n) l <<= 1;
  offset(f, m + 1, m, tA);
  for (int i = 0; i <= m; ++i) tB[i] = f[i];
  for (int i = m + 1; i < l; ++i) tA[i] = tB[i] = 0;
  DFT(tA, l); DFT(tB, l);
  for (int i = 0; i < l; ++i) tA[i] = tA[i] * tB[i] % mod;
  IDFT(tA, l);
  if (n & 1)
    for (int i = 0; i <= n; ++i)
      f[i] = ((i ? tA[i - 1] : 0) + (n - 1) * tA[i]) % mod;
  else
    for (int i = 0; i <= n; ++i)
      f[i] = tA[i];
}

LL f[N];

int main() {
  int n;
  scanf("%d", &n);
  Init(n * 2);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) inv[i] = -(mod / i) * inv[mod % i] % mod;
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
  Solve(n, f);
  for (int i = 0; i <= n; ++i)
    printf("%lld ", (f[i] + mod) % mod);
  return 0;
}

