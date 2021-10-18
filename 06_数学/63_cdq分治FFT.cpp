// hdu 7054
// 求解(1+x^{a1})*(1+x^{a2})*...*(1+x^{an})
// \sum_{i=1}^n a_i <= 1e6.

// 可以f[i][j]，前i个数的和为j的方案数，可以用生成函数转换，并用多项式求解，同时分治FFT优化。

const int N = 1e5 + 10;
int tr[N];
int getLen(int n) ;

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

struct Poly {
    ll *p;
    int len;
    void init(int len) {
        p = a + cnt;
        this -> len = len;
        for(int i = 0;i <= len; i++) p[i] = read();
        cnt += len + 1;
    }

    void mul(const Poly b) {
        static ll x[N], y[N];
        int LEN = getLen(len + b.len);
        for(int i = 0;i <= len; i++) x[i] = p[i];
        for(int i = 0;i <= b.len; i++) y[i] = b.p[i];
        for(int i = len + 1;i <= LEN; i++) x[i] = 0;
        for(int i = b.len + 1;i <= LEN; i++) y[i] = 0;
        MTT(x, y, p, LEN);
        this -> len += b.len;
        // 不知道为啥要两倍，可能会有不为0的情况，管他呢
        for(int i = len + 1;i <= 2 * LEN; i++) p[i] = 0;
        for(int i = 0;i <= LEN; i++) x[i] = y[i] = 0;
    }
};

Poly cdq(int l, int r) {
    Poly res;
    if(l == r) res.init(len); // 长度
    else {
        int mid = (l + r) / 2;
        res = cdq(l, mid);
        res.mul(cdq(mid + 1, r));
    }
    return res;
}

void solve() {
    mem(a, 0);
    int n = read();
    cnt = 0;
    ll ans = 1;
    Poly res = cdq(1, n);
    for(int i = 0;i < n; i++) cout << res.p[i] << " ";
}