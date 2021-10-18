// 线段树维护LIS输出字典序最小的路径
const int N = 1e5 + 10;

#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) / 2

struct Tree {
    int l, r;
    int mx;
    int id;
}t[N << 2];

inline void push_up(int u) {
    if (t[lc].mx > t[rc].mx)
        t[u].mx = t[lc].mx, t[u].id = t[lc].id;
    else if (t[lc].mx < t[rc].mx)
        t[u].mx = t[rc].mx, t[u].id = t[rc].id;
    else
        t[u].mx = t[lc].mx, t[u].id = min(t[lc].id, t[rc].id);
}

void build(int u, int l, int r) {
    t[u].l = l;
    t[u].r = r;
    t[u].mx = t[u].id = 0;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    push_up(u);
}

void modify(int u, int ql, int qr, int val, int id) {
    if (ql <= t[u].l && t[u].r <= qr) {
        if (t[u].mx < val || (t[u].mx == val && t[u].id > id)) {
            t[u].mx = val;
            t[u].id = id;
        }
        return;
    }
    if (ql <= mid)
        modify(lc, ql, qr, val, id);
    if (qr > mid)
        modify(rc, ql, qr, val, id);
    push_up(u);
}

pii query(int u, int ql, int qr) {
    if (ql <= t[u].l && t[u].r <= qr)
        return pii{t[u].mx, t[u].id};
    pii lson = {-1, -1}, rson = {-1, -1};
    if (ql <= mid)
        lson = query(lc, ql, qr);
    if (qr > mid)
        rson = query(rc, ql, qr);
    if (lson.x > rson.x)
        return lson;
    else if (lson.x < rson.x)
        return rson;
    else
        return {lson.x, min(lson.y, rson.y)};
}

void solve() {
    int n;
    cin >> n;
    assert(1 <= n && n <= 1e5);
    build(1, 1, 1e5);
    vector<int> a(n + 1), ans(n + 1), fa(n + 1);
    pii res = {0, 0};
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        assert(1 <= a[i] && a[i] <= 1e5);
        if (a[i] == 1) {
            fa[i] = 0;
            ans[i] = 1;
            modify(1, a[i], a[i], 1, i);
            continue;
        }
        pii temp = query(1, 1, a[i] - 1);
        ans[i] = temp.x + 1;
        fa[i] = temp.y;
        modify(1, a[i], a[i], ans[i], i);
        if (res.x < ans[i])
            res = pii{ans[i], i};
    }
    vector<int> v;
    int tt = res.second;
    while (tt) {
        v.push_back(tt);
        tt = fa[tt];
    }
    cout << v.size() << endl;
    for (int i = v.size() - 1; i >= 0; i--) {
        cout << v[i] << (i == 0 ? endl : " ");
    }
}


// 线段树维护LIS方案数
