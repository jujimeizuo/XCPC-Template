const int N = 4e6 + 10;

int n, k;
struct node {
    int a, b, c;
    int operator < (const node &o) const {
        return a != o.a ? (a < o.a) : (b != o.b ? (b < o.b) : (c < o.c));
    }

    int operator == (const node &o) const {
        return a == o.a && b == o.b && c == o.c;
    }
}p[N];


struct Tree1 {
    int l, r;
}t1[N << 2];

struct Tree2 {
    int l, r;
    int num;
}t2[N << 2];

int root, root2[N];
int cnt1, cnt2;

void vec_insert(int &u, int l, int r, int pos, int val) {
    if(!u) u = ++cnt2;
    t2[u].num += val;
    if(l == r) return ;
    int m = (l + r) / 2;
    if(pos <= m) vec_insert(t2[u].l, l, m, pos, val);
    else vec_insert(t2[u].r, m + 1, r, pos, val);
}

int vec_query(int u, int l, int r, int ql, int qr) {
    if(!u) return 0;
    if(ql <= l && r <= qr) return t2[u].num;
    int ans = 0;
    int mid = (l + r) / 2;
    if(ql <= mid) ans += vec_query(t2[u].l, l, mid, ql, qr);
    if(qr  > mid) ans += vec_query(t2[u].r, mid + 1, r, ql, qr);
    return ans;
}

// 在第一维权值线段树在[1,k]根据p[x].b插入，第二维权值线段树在[1,k]根据p[x].c插入
void tree_insert(int &u, int l, int r, int x, int val) {
    if(!u) u = ++cnt1;
    vec_insert(root2[u], 1, k, p[x].c, val);
    if(l == r) return ;
    int m = (l + r) / 2;
    if(p[x].b <= m) tree_insert(t1[u].l, l, m, x, val);
    else tree_insert(t1[u].r, m + 1, r, x, val);
}

int tree_query(int u, int l, int r, int x) {
    if(!u) return 0;
    if(1 <= l && r <= p[x].b) return vec_query(root2[u], 1, k, 1, p[x].c);
    int mid = (l + r) / 2;
    int ans = 0;
    if(1 <= mid) ans += tree_query(t1[u].l, l, mid, x);
    if(p[x].b > mid) ans += tree_query(t1[u].r, mid + 1, r, x);
    return ans;
}

void solve() {
    cin >> n >> k;
    for(int i = 1;i <= n; i++) cin >> p[i].a >> p[i].b >> p[i].c;
    sort(p + 1, p + n + 1);
    vector<int> ans(n + 1);
    int sum = 1;
    for(int i = 1;i <= n; i++) {
        // 因为这些个都一样，如果不这样操作，会使后面的不会对前面的有贡献
        if(p[i + 1] == p[i]) {
            sum++;
            continue;
        }
        tree_insert(root, 1, k, i, sum);
        int res = tree_query(root, 1, k, i);
        ans[res] += sum;
        sum = 1;
    }
    for(int i = 1;i <= n; i++) cout << ans[i] << endl;
}
