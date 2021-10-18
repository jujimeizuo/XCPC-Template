const int N = 2e5 + 10;

#define lc u << 1
#define rc u << 1 | 1

struct Tree {
    int sum, tag;
}t[21][N << 2];
int a[N];

void push_up(int id, int u) {
    t[id][u].sum = t[id][lc].sum + t[id][rc].sum;
}

void push_down(int id, int u, int l, int r) {
    if(!t[id][u].tag) return ;
    int m = (l + r) / 2;
    t[id][lc].sum = (m - l + 1) - t[id][lc].sum;
    t[id][rc].sum = (r - m) - t[id][rc].sum;
    t[id][lc].tag ^= 1;
    t[id][rc].tag ^= 1;
    t[id][u].tag = 0;
}

void build(int id, int u, int l, int r) {
    if(l == r) {
        t[id][u].sum = (a[l] >> id) & 1;
        t[id][u].tag = 0;
        return ;
    }
    int m = (l + r) / 2;
    build(id, lc, l, m);
    build(id, rc, m + 1, r);
    push_up(id, u);
}

void modify(int id, int u, int l, int r, int ql, int qr) {
    if(ql <= l && r <= qr) {
        t[id][u].sum = (r - l + 1) - t[id][u].sum;
        t[id][u].tag ^= 1;
        return ;
    }
    push_down(id, u, l, r);
    int m = (l + r) / 2;
    if(ql <= m) modify(id, lc, l, m, ql, qr);
    if(qr  > m) modify(id, rc, m + 1, r, ql, qr);
    push_up(id, u);
}

int query(int id, int u, int l, int r, int ql, int qr) {
    if(ql <= l && r <= qr) return t[id][u].sum;
    push_down(id, u, l, r);
    int ans = 0;
    int m = (l + r) / 2;
    if(ql <= m) ans += query(id, lc, l, m, ql, qr);
    if(qr  > m) ans += query(id, rc, m + 1, r, ql, qr);
    return ans;
}

void solve() {
    int n, m; cin >> n >> m;
    for(int i = 1;i <= n; i++) cin >> a[i];
    for(int i = 0;i <= 20; i++) {
        build(i, 1, 1, n);
    }
    while(m--) {
        int opt; cin >> opt;
        if(opt == 1) {
            int l, r; cin >> l >> r;
            ll ans = 0;
            for(int i = 0;i <= 20; i++) {
                ans += query(i, 1, 1, n, l, r) * (1ll << i);
            }
            cout << ans << endl;
        }
        else {
            int l, r, k; cin >> l >> r >> k;
            for(int i = 0;i <= 20; i++) {
                if((k >> i) & 1) modify(i, 1, 1, n, l, r);
            }
        }
    }
}
