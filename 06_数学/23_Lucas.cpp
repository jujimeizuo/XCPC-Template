class Comb {
public :
    const int n;;
    std::vector<Z> fac, inv, ifac;
    Comb(int n) : n(n), fac(n), inv(n), ifac(n) {
        fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
        for(int i = 2;i < n; i++) {
            fac[i] = fac[i - 1] * i;
            inv[i] = (P - P / i) * inv[P % i];
            ifac[i] = ifac[i - 1] * inv[i];
        }
    }
    Z C(int n, int m) {
        if(m < 0 || n < 0 || m > n) return 0;
        return fac[n] * ifac[m] * ifac[n - m];
    }
    Z Lucas(long long m, long long n) { return n ? Lucas(m / P, n / P) * C(m % P, n % P) : 1;}
};
