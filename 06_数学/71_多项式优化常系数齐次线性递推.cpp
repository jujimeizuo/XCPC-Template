
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = acos(-1);
const int N = 3e5 + 10;

struct Complex {
    double x, y;
    Complex(double a = 0, double b = 0): x(a), y(b) {}
    Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
    Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
    Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Complex conj() { return Complex(x, -y); }
} w[N];

ll mod;
int n, k, len, tr[N];
ll a[N], h[N], ans[N], s[N], invG[N], G[N];

ll quick_pow(ll a, ll b) ;

int getLen(int n) ;

void rever(ll *f, int n) ;

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

void Get_Inv(ll *f, ll *g, int n) ;


void Mod(ll *f,ll *g) {
    static ll tmp[N];
    rever(f, k + k - 1);
    for(int i = 0;i < k; i++) tmp[i] = f[i];
    MTT(tmp, invG, tmp, len);
    for(int i = k - 1; i < len; i++) tmp[i] = 0;
    rever(f, k + k - 1); rever(tmp, k - 1);
    MTT(tmp, G, tmp, len);
    for(int i = 0;i < k; i++) g[i] = (f[i] + mod - tmp[i]) % mod;
    for(int i = k;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) tmp[i] = 0;
}
void fpow(int b) {
	s[1] = 1; ans[0] = 1;
	while(b) {
		if(b & 1) { MTT(ans, s, ans, len); Mod(ans, ans); }
		MTT(s, s, s, len); Mod(s, s);
		b >>= 1;
	}
}

ll DITI(ll *a, ll *h, ll *ans, int n, int k) {
    G[k] = 1; for(int i = 1;i <= k; i++) G[k - i] = (mod - a[i]) % mod;
    rever(G, k + 1);
    len = getLen(k + 1);
    Get_Inv(G, invG, k + 1);
    for(int i = k + 1;i < len; i++) invG[i] = 0;
    rever(G, k + 1);
    fpow(n);
    ll Ans = 0;
    for(int i = 0;i < k; i++) Ans = (Ans + 1ll * h[i] * ans[i] % mod) % mod;
    return Ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1;i <= k; i++){ cin >> a[i]; a[i] = a[i] < 0 ? a[i] + mod : a[i]; }
    for(int i = 0;i < k; i++) { cin >> h[i]; h[i] = h[i] < 0 ? h[i] + mod : h[i]; }

    ll Ans = DITI(a, h, ans, n, k);
    cout << Ans << endl;
}