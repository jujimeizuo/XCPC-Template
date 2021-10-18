// 线段树维护序列总LIS的长度mx.fi和方案数mx.se
// 以及对于每个点，可以存在于多少个LIS种

// https://nanti.jisuanke.com/t/39611

namespace Tree_LIS {
    const int N = 1e6 + 10;

#define lc t[u].l
#define rc t[u].r
#define mid (l + r) / 2

    struct Tree {
        int l, r;
        ll len; // 长度
        ll sum; // 个数
    }t[N << 2];

    int root, cnt;
    void init() {
        mem(t, 0);
        cnt = root = 0;
    }

    void push_up(int u) {
        if(t[lc].len == t[rc].len) {
            t[u].len = t[lc].len;
            t[u].sum = (t[lc].sum + t[rc].sum) % mod;
        }
        else if(t[lc].len < t[rc].len) {
            t[u].len = t[rc].len;
            t[u].sum = t[rc].sum;
        }
        else {
            t[u].len = t[lc].len;
            t[u].sum = t[lc].sum;
        }
    }

    void modify(int &u, int l, int r, int p, int le, int su) {
        if(!u) u = ++cnt;
        if(l == r) {
            if(t[u].len == le) t[u].sum = (t[u].sum + su) % mod;
            else if(t[u].len < le) {
                t[u].len = le;
                t[u].sum = su;
            }
            return ;
        }
        if(!lc) lc = ++cnt;
        if(!rc) rc = ++cnt;
        if(p <= mid) modify(lc, l, mid, p, le, su);
        else modify(rc, mid + 1, r, p, le, su);
        push_up(u);
    }

    pll query(int u, int l, int r, int ql, int qr) {
        if(ql <= l && r  <= qr) return pll{t[u].len, t[u].sum};
        pll lson = {0, 0}, rson = {0, 0};
        if(!lc) lc = ++cnt;
        if(!rc) rc = ++cnt;
        if(ql <= mid) lson = query(lc, l, mid, ql, qr);
        if(qr  > mid) rson = query(rc, mid + 1, r, ql, qr);
        if(lson.fi == rson.fi) return pll{lson.fi, (lson.se + rson.se) % mod};
        else if(lson.fi < rson.fi) return rson;
        else return lson;
    }
};

using namespace Tree_LIS;

ll quick_pow(ll a, ll b) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

void solve() {
    int n; cin >> n;
    int L = 0, R = 1e9 + 7;
    vector<int> a(n + 1);
    vector<pll> l(n + 1), r(n + 1);
    for(int i = 1;i <= n; i++) cin >> a[i];
    init();
    modify(root, L, R, a[1], 1, 1);
    l[1] = {1, 1};
    for(int i = 2;i <= n; i++) {
        pll temp = query(root, L, R, 0, a[i] - 1);
        if(temp.fi == 0) temp = {0, 1};
        modify(root, L, R, a[i], temp.fi + 1, temp.se);
        l[i] = {temp.fi + 1, temp.se};
    }
    pll mx = query(root, L, R, 0, R);
    init();
    modify(root, L, R, R - a[n], 1, 1);
    r[n] = {1, 1};
    for(int i = n - 1;i >= 1; i--) {
        pll temp = query(root, L, R, 0, R - a[i] - 1);
        if(temp.fi == 0) temp = {0, 1};
        modify(root, L, R, R - a[i], temp.fi + 1, temp.se);
        r[i] = {temp.fi + 1, temp.se};
    }
    for(int i = 1;i <= n; i++) {
        if(r[i].fi + l[i].fi - 1 == mx.fi) {
            cout << (r[i].se * l[i].se % mod * quick_pow(mx.se, mod - 2) % mod + mod) % mod << " ";
        }
        else cout << 0 << " ";
    }
    cout << endl;
}
