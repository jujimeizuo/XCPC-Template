const int N = 2e5 + 10;

int n, m, l, r, a, b, num[N], Last[N], pre[N], Hash[N], ans[N][2];
int cnt, root[N], sum[N * 20], lc[N * 20], rc[N * 20];
struct Query {
    int a, b, l, id;
};

struct data {
    int a, v;

    bool operator<(const data &b) const {
        return a < b.a;
    }
} d[N];

vector<Query> q[N * 4];

void addquery(int o, int l, int r, int L, int R, Query qry) {
    if (L <= l && R >= r) {
        q[o].push_back(qry);
        return;
    }
    int mid = (l + r) / 2;
    if (L <= mid) {
        addquery(o * 2, l, mid, L, R, qry);
    }
    if (R > mid) {
        addquery(o * 2 + 1, mid + 1, r, L, R, qry);
    }
}

void build(int y, int &x, int l, int r, int k) {
    x = ++cnt;
    sum[x] = sum[y] + 1;
    lc[x] = lc[y];
    rc[x] = rc[y];
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (k <= mid) {
        build(lc[y], lc[x], l, mid, k);
    } else {
        build(rc[y], rc[x], mid + 1, r, k);
    }
}

int query(int y, int x, int l, int r, int k) {
    if (!x || l == r) {
        return 0;
    }
    int mid = (l + r) / 2;
    if (k <= mid) {
        return query(lc[y], lc[x], l, mid, k);
    } else {
        return sum[lc[x]] - sum[lc[y]] + query(rc[y], rc[x], mid + 1, r, k);
    }
}

void insert(int o, int l, int r) {
    if (q[o].size()) {
        Hash[0] = 0;
        for (int i = l; i <= r; i++) {
            Hash[++Hash[0]] = num[i];
        }
        sort(Hash + 1, Hash + Hash[0] + 1);
        int s = 0;
        for (int i = l; i <= r; i++) {
            d[++s].a = lower_bound(Hash + 1, Hash + Hash[0] + 1, num[i]) - Hash;
            d[s].v = pre[i];
        }
        sort(d + 1, d + s + 1);
        for (int i = 1; i <= s; i++) {
            build(root[i - 1], root[i], 0, n, d[i].v);
        }
        int a, b;
        for (int i = 0; i < q[o].size(); i++) {
            a = lower_bound(Hash + 1, Hash + Hash[0] + 1, q[o][i].a) - Hash;
            b = upper_bound(Hash + 1, Hash + Hash[0] + 1, q[o][i].b) - Hash - 1;
            ans[q[o][i].id][0] += sum[root[b]] - sum[root[a - 1]];
            ans[q[o][i].id][1] += query(root[a - 1], root[b], 0, n, q[o][i].l);
        }
        memset(root, 0, sizeof(int) * (Hash[0] + 1));
        memset(sum, 0, sizeof(int) * (cnt + 1));
        memset(lc, 0, sizeof(int) * (cnt + 1));
        memset(rc, 0, sizeof(int) * (cnt + 1));
        cnt = 0;
    }
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    insert(o * 2, l, mid);
    insert(o * 2 + 1, mid + 1, r);
}

void solve() {
    int _;
    cin >> _;
    while (_--) {
        for (int i = 0; i < N * 4; i++) q[i].clear();
        cnt = 0;
        for (int i = 0; i < N; i++) ans[i][0] = ans[i][1] = pre[i] = Last[i] = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> num[i];
            num[i]++;
            pre[i] = Last[num[i]];
            Last[num[i]] = i;
        }
        for (int i = 1; i <= m; i++) {
            cin >> l >> a >> r >> b;
            a++, b++;
            addquery(1, 1, 1e5 + 1, l, r, (Query) {a, b, l, i});
        }
        insert(1, 1, 1e5 + 1);
        for (int i = 1; i <= m; i++) {
            cout << ans[i][1] << endl;
        }
    }
}
