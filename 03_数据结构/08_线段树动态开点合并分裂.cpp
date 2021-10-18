#define mid (l+r)/2
static const int MAX_N = N * 40;
int rt[N], now;
int lc[MAX_N], rc[MAX_N];
ll sum[MAX_N];
int tot, rub[MAX_N];
int newNode() { return rub[0] ? rub[rub[0]--] : ++tot; }
void remove(int &u) {
    lc[u] = rc[u] = sum[u] = 0;
    rub[++rub[0]] = u;
    u = 0;
}
void push_up(int u) { sum[u] = sum[lc[u]] + sum[rc[u]]; }
void build(int &u, int l, int r) {
    u = newNode();
    if (l == r) {
        sum[u] = cnt[l];
        return;
    }
    build(lc[u], l, mid); build(rc[u], mid + 1, r);
    push_up(u);
}
void update(int &u, int l, int r, int p, ll k) {
    if (!u) u = newNode();
    if (l == r) {
        sum[u] += k;
        return;
    }
    if (p <= mid) update(lc[u], l, mid, p, k);
    else update(rc[u], mid + 1, r, p, k);
    push_up(u);
}
ll querySum(int u, int l, int r, int ql, int qr) {
    if (!u) return 0;
    if (ql <= l && r <= qr) return sum[u];
    ll res = 0;
    if (ql <= mid) res += querySum(lc[u], l, mid, ql, qr);
    if (qr > mid) res += querySum(rc[u], mid + 1, r, ql, qr);
    return res;
}
int queryKth(int u, int l, int r, ll k) {
    if (l == r) return l;
    if (k <= sum[lc[u]]) return queryKth(lc[u], l, mid, k);
    else return queryKth(rc[u], mid + 1, r, k - sum[lc[u]]);
}
void merge(int u, int v, int l, int r) {
    if (l == r) {
        sum[u] += sum[v];
        return;
    }
    if (lc[u] && lc[v]) merge(lc[u], lc[v], l, mid), remove(lc[v]);
    else if (lc[v]) lc[u] = lc[v], lc[v] = 0;
    if (rc[u] && rc[v]) merge(rc[u], rc[v], mid + 1, r), remove(rc[v]);
    else if (rc[v]) rc[u] = rc[v], rc[v] = 0;
    push_up(u);
}
void split(int &newp, int &u, int l, int r, int ql, int qr) {//分裂出[ql, qr]间的点
    if (!u) return;
    if (ql <= l && r <= qr) {
        newp = u;
        u = 0;
        return;
    }
    if (!newp) newp = newNode();
    if (ql <= mid) split(lc[newp], lc[u], l, mid, ql, qr);
    if (qr > mid) split(rc[newp], rc[u], mid + 1, r, ql, qr);
    push_up(u);
    push_up(newp);

}
#undef mid
