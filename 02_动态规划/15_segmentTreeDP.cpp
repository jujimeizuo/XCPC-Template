const ll INF = 0x3f3f3f3f;

#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) / 2

const int N = 3e5 + 10;
const int K = 100 + 10;
int dp[N][K];

struct Tree {
    int l, r;
    int mn;
    int tag;
}t[N << 1];

inline void push_up(int u) {
    t[u].mn = min(t[lc].mn, t[rc].mn);
}

inline void push_down(int u) {
    if(!t[u].tag) return ;
    t[lc].tag += t[u].tag;
    t[rc].tag += t[u].tag;
    t[lc].mn  += t[u].tag;
    t[rc].mn  += t[u].tag;
    t[u].tag = 0;
}

void build(int u, int l, int r, int k) {
    t[u].l = l; t[u].r = r;
    t[u].tag = 0; t[u].mn = INF;
    if(l == r) {
        t[u].mn = dp[l][k];
        return ;
    }
    int m = (l + r) / 2;
    build(lc, l, m, k);
    build(rc, m + 1, r, k);
    push_up(u);
}

void modify(int u, int ql, int qr, int val) {
    if(ql <= t[u].l && t[u].r <= qr) {
        t[u].mn += val;
        t[u].tag += val;
        return ;
    }
    push_down(u);
    if(ql <= mid) modify(lc, ql, qr, val);
    if(qr >  mid) modify(rc, ql, qr, val);
    push_up(u);
}

int query(int u, int ql, int qr) {
    if(ql <= t[u].l && t[u].r <= qr) return t[u].mn;
    push_down(u);
    int ans = INF;
    if(ql <= mid) ans = min(ans, query(lc, ql, qr));
    if(qr  > mid) ans = min(ans, query(rc, ql, qr));
    return ans;
}


void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n + 1), pre(n + 1, -1), from(n + 1);
    for(int i = 1;i <= n; i++) cin >> a[i];

    for(int i = 1;i <= n; i++) {
        dp[i][1] = dp[i - 1][1];
        from[i] = pre[a[i]];
        if(from[i] != -1) dp[i][1] += i - from[i];
        pre[a[i]] = i;
    }

    for(int i = 2;i <= k; i++) {
        build(1, 1, n, i - 1);
        for(int j = i;j <= n; j++) {
            if(from[j] != -1) modify(1, 1, from[j] - 1, j - from[j]);
            dp[j][i] = min(dp[j - 1][i - 1], query(1, i - 1, j - 1));
            // cout << j << " " << "分成" << i << "段：" << " " << dp[j][i] << endl;
        }
    }
    cout << dp[n][k] << endl;
}

signed main() {
    solve();
}
