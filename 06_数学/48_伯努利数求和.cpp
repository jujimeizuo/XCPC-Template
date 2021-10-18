namespace BNL {
    const int N = 1e7 + 10, M = 1e6 + 10;
    struct Complex {
        double x, y;
        Complex(double a = 0, double b = 0): x(a), y(b) {}
        Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
        Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
        Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
        Complex conj() { return Complex(x, -y); }
    } w[N];

    int tr[N];
    ll F[N], G[N];

    ll quick_pow(ll a, ll b, ll p) {
        ll ans = 1;
        while(b) {
            if(b & 1) ans = ans * a % p;
            a = a * a % p;
            b >>= 1;
        }
        return ans % p;
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

    inline void MTT(ll *x, ll *y, ll *z, int n) {
        int len = 1; while (len <= n) len <<= 1;
        for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
        for (int i = 0; i < len; i++) w[i] = w[i] = Complex(cos(2 * PI * i / len), sin(2 * PI * i / len));

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
            int da = (ll)(a[i].x / len + 0.5) % mod;
            int db = (ll)(a[i].y / len + 0.5) % mod;
            int dc = (ll)(b[i].x / len + 0.5) % mod;
            int dd = (ll)(b[i].y / len + 0.5) % mod;
            z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
        }
    }

    int getLen(int n) {
        int len = 1; while (len < (n << 1)) len <<= 1;
        for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
        for (int i = 0; i < len; i++) w[i] = w[i] = Complex(cos(2 * PI * i / len), sin(2 * PI * i / len));
        return len;
    }

    void Get_Inv(ll *f, ll *g, int n) {
        if(n == 1) { g[0] = quick_pow(f[0], mod - 2, mod); return ; }
        Get_Inv(f, g, (n + 1) >> 1);
        int len = getLen(n);
        static ll c[N];
        for(int i = 0;i < len; i++) c[i] = i < n ? f[i] : 0;
        MTT(c, g, c, len); MTT(c, g, c, len);
        for(int i = 0;i < n; i++) g[i] = (2ll * g[i] - c[i] + mod) % mod;
        for(int i = n;i < len; i++) g[i] = 0;
        for(int i = 0;i < len; i++) c[i] = 0;
    }

    ll ff[N], invff[N], inv[N];
    ll B[N];

    ll C(ll m, ll n) {
        if(m < 0 || n < 0 || n > m)
            return 0;
        ll ans = ff[m];
        ans = ans * invff[n] % mod;
        ans = ans * invff[m - n] % mod;
        return ans;
    }

    void init(int m) {
        ff[0] = ff[1] = inv[0] = inv[1] = invff[0] = invff[1] = 1;
        for(int i = 2;i < M; i++)
        {
            ff[i] = ff[i - 1] * i % mod;
            inv[i] = mod - (mod / i) * inv[mod % i] % mod;
            invff[i] = invff[i - 1] * inv[i] % mod;
        }

        for(int i = 0;i <= m + 10; i++) F[i] = invff[i + 1];
        Get_Inv(F, G, m + 10);
        for(int i = 0;i <= m + 10; i++) B[i] = G[i] * ff[i] % mod;
    }

    ll solve(ll n, int k) {
        init(k);
        ll ans = 0, prod = n % mod;
        for(int i = k; ~i ; i--) {
            ans = (ans + prod * B[i] % mod * C(k + 1, i) % mod) % mod;
            prod = prod * n % mod;
        }
        ans = ans * quick_pow(k + 1, mod - 2, mod) % mod;
        return ans;
    }
}

void solve() {
    ll n; int k; cin >> n >> k;
    cout << BNL::solve(n + 1, k) << endl;
}