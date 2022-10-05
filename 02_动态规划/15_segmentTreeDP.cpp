#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) / 2
 
const int N = 3e5 + 10;
const int K = 100 + 10;
int n, k;
int dp[N][K];
 
struct Tree {
    int l, r;
    int mx;
    int tag;
}t[N << 2];
 
inline void push_up(int u) {
    t[u].mx = max(t[lc].mx, t[rc].mx);
}
 
inline void push_down(int u) {
    if(!t[u].tag) return ;
    t[lc].tag += t[u].tag;
    t[rc].tag += t[u].tag;
    t[lc].mx  += t[u].tag;
    t[rc].mx  += t[u].tag;
    t[u].tag = 0;
}
 
void build(int u, int l, int r, int k) {
    t[u].l = l; t[u].r = r;
    t[u].tag = t[u].mx = 0;
    if(l == r) {
        t[u].mx = dp[l][k];
        return ;
    }
    int m = (l + r) / 2;
    build(lc, l, m, k);
    build(rc, m + 1, r, k);
    push_up(u);
}
 
void modify(int u, int ql, int qr, int val) {
    if(ql <= t[u].l && t[u].r <= qr) {
        t[u].mx += val;
        t[u].tag += val;
        return ;
    }
    int ans = -INF;
    push_down(u);
    if(ql <= mid) modify(lc, ql, qr, val);
    if(qr  > mid) modify(rc, ql, qr, val);
    push_up(u);
}
 
int query(int u, int ql, int qr) {
    if(ql <= t[u].l && t[u].r <= qr) return t[u].mx;
    push_down(u);
    int ans = 0;
    if(ql <= mid) ans = max(ans, query(lc, ql, qr));
    if(qr  > mid) ans = max(ans, query(rc, ql, qr));
    return ans;
}
 
void solve() {
    cin >> n >> k;
    vector<int> a(n + 1), pre(n + 1), from(n + 1);
    set<int> s;
    for(int i = 1;i <= n; i++) {
        cin >> a[i];
        s.insert(a[i]);
        from[i] = pre[a[i]]; pre[a[i]] = i;
        dp[i][1] = (int)s.size();
    }
    for(int i = 2;i <= k; i++) {
        build(1, 1, n, i - 1);
        for(int j = i;j <= n; j++) {
            modify(1, from[j], j - 1, 1);
            dp[j][i] = max(dp[j - 1][i - 1] + 1, query(1, i - 1, j - 1));
        }
    }
    cout << dp[n][k] << endl;
}