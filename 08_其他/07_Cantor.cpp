  
//主要应用为将N维的排列状态压缩成数字id
//然后需要知道具体状态时用逆Cantor得到

int N;
int a[MAX], c[MAX];

void upd(int p, int k) { for (; p <= N; p += lowbit(p)) c[p] += k; }
int query(int p) {
    int res = 0;
    for (; p; p -= lowbit(p)) res += c[p];
    return res;
}

int cantor() {
    //ans = 1 + \sum_{i = 1} ^ {N} fac[N - i] * (\sum_{j = i + 1} ^ {N} x[i] > x[j])
    int res = 0, fac = 1;
    for (int i = N; i >= 1; i--) {
        upd(a[i], 1);
        res = (res + 1ll * fac * query(a[i] - 1) % mod) % mod;
        fac = 1ll * fac * (N - i + 1) % mod;
    }
    return res + 1;
}

//逆Cantor
#define lc  u<<1
#define rc  u<<1|1
#define mid (l+r)/2
int sum[MAX << 4];
void push_up(int u) { sum[u] = sum[lc] + sum[rc]; }
void build(int u, int l, int r) {
    if (l == r) {
        sum[u] = 1;
        return;
    }
    build(lc, l, mid); build(rc, mid + 1, r);
    push_up(u);
}
int query(int u, int l, int r, int k) {//查找第k大并且删除该数
    sum[u]--;
    if (l == r) return l;
    if (k <= sum[lc]) return query(lc, l, mid, k);
    else return query(rc, mid + 1, r, k - sum[lc]);
}

vector<int> inCantor(int x, int n) {
    x--;
    vector<int> res;
    ll fac = 1;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) fac = fac * i;
    for (int i = 1; i <= n; i++) {
        fac = fac / (n - i + 1);
        int k = x / fac + 1;//比当前这位大的有x / fac位
        res.push_back(query(1, 1, n, k));//找到没被选的第k大
        x %= fac;
    }
    return res;
}