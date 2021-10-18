// mod一定为质数

namespace Comb {
    ll mod;
    const int N = 1e6 + 10;
    ll F[N], invF[N], inv[N];

    void init() {
        F[0] = F[1] = invF[0] = invF[1] = inv[0] = inv[1] = 1;
        for (int i = 2; i < N; i++) {
            F[i] = F[i - 1] * i % mod;
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            invF[i] = invF[i - 1] * inv[i] % mod;
        }
    }

    ll C(ll m, ll n) {
        if (m < 0 || n < 0 || n > m) return 0;
        ll ans = F[m];
        ans = ans * invF[n] % mod;
        ans = ans * invF[m - n] % mod;
        return ans;
    }

    ll Lucas(ll m, ll n) {
        return n ? Lucas(m / mod, n / mod) * C(m % mod, n % mod) % mod : 1;
    }

}

// Comb::Lucas(m, n)