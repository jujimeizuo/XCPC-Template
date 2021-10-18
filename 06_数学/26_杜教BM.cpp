typedef long long ll;
const ll mod = 1e9 + 7;

typedef vector<ll> VI;

ll quick_pow(ll a, ll b) ;

namespace linear_seq {
    const ll N = 1e5 + 10;
    ll res[N], base[N], _c[N], _md[N];

    vector<ll> Md;
    void mul(ll *a, ll *b, ll k) {
        for (ll i = 0; i < 2 * k; i++)
            _c[i] = 0;
        for (ll i = 0; i < k; i++) {
            if (a[i]) {
                for (int j = 0; j < k; j++) {
                    _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
                }
            }
        }
        for (ll i = 2 * k - 1; i >= k; i--) {
            if (_c[i]) {
                for (ll j = 0; j < Md.size(); j++) {
                    _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
                }
            }
        }
        for (ll i = 0; i < k; i++)
            a[i] = _c[i];
    }

    ll solve(ll n, VI a, VI b) {
        // a 系数 b 初值 b[n + 1] = a[0] * b[n] + ...
        // cout << b.size() << endl;
        ll ans = 0, pnt = 0;
        ll k = a.size();
        assert(a.size() == b.size());
        for (ll i = 0; i < k; i++)
            _md[k - i - 1] = -a[i];
        _md[k] = 1;
        Md.clear();
        for (ll i = 0; i < k; i++) {
            if (_md[i] != 0)
                Md.push_back(i);
        }
        for (ll i = 0; i < k; i++)
            res[i] = base[i] = 0;
        res[0] = 1;
        while ((1ll << pnt) <= n)
            pnt++;
        for (ll p = pnt; p >= 0; p--) {
            mul(res, res, k);
            if ((n >> p) & 1) {
                for (ll i = k - 1; i >= 0; i--)
                    res[i + 1] = res[i];
                res[0] = 0;
                for (ll i = 0; i < Md.size(); i++)
                    res[Md[i]] = (res[Md[i]] - res[k] * _md[Md[i]]) % mod;
            }
        }
        for (ll i = 0; i < k; i++)
            ans = (ans + res[i] * b[i]) % mod;
        return ans;
    }

    VI BM(VI s) {
        VI C(1, 1), B(1, 1);
        ll L = 0, m = 1, b = 1;
        for (ll n = 0; n < s.size(); n++) {
            ll d = 0;
            for (ll i = 0; i < L + 1; i++)
                d = (d + (ll)C[i] * s[n - i]) % mod;
            if (d == 0)
                m++;
            else if (2 * L <= n) {
                VI T = C;
                ll c = mod - d * quick_pow(b, mod - 2) % mod;
                while (C.size() < B.size() + m)
                    C.push_back(0);
                for (int i = 0; i < B.size(); i++)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L;
                B = T;
                b = d;
                m = 1;
            }
            else {
                ll c = mod - d * quick_pow(b, mod - 2) % mod;
                while (C.size() < B.size() + m)
                    C.push_back(0);
                for (ll i = 0; i < B.size(); i++)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                m++;
            }
        }
        return C;
    }

    ll gao(VI a, ll n) {
        VI c = BM(a);
        c.erase(c.begin());
        for (ll i = 0; i < c.size(); i++)
            c[i] = (mod - c[i]) % mod;
        return solve(n, c, VI(a.begin(), a.begin() + c.size()));
    }
}

void solve() {
    int n;
    while (~scanf("%d", &n)) {
        VI v = VI{1,2,4,7,13,24};
            printf("%d\n", linear_seq::gao(v, n - 1));
    }
}