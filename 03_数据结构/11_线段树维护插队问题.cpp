// n个人，每个人a_i要顺序坐在pos_i，问最终的序列如何
// 最后一个人一定坐在自己喜欢坐的位置，去掉该位置，倒数第二个人成为最后一个人，所以就是查找空位置的第pos位置

const int N = 4e5 + 10;

#define lc u << 1
#define rc u << 1 | 1
#define mid (l + r) / 2
int sum[N << 2], ans[N];

void push_up(int u) {
    sum[u] = sum[lc] + sum[rc];
}

void build(int u, int l, int r) {
    if(l == r) {
        sum[u] = 1;
        ans[l] = 0;
        return ;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    push_up(u);
}

void modify(int u, int l, int r, int k, int val) {
    if(l == r) {
        ans[l] = val;
        sum[u] = 0;
        return ;
    }
    if(sum[lc] >= k) modify(lc, l, mid, k, val);
    else modify(rc, mid + 1, r, k - sum[lc], val);
    push_up(u);
}

void solve() {
    int n;
    while(~scanf("%d", &n)) {
        vector<pii> p(n + 1);
        for(int i = 1;i <= n; i++) {
            scanf("%d%d",&p[i].fi, &p[i].se);
        }
        build(1, 1, n);
        for(int i = n;i >= 1; i--) {
            modify(1, 1, n, p[i].fi + 1, p[i].se);
        }
        for(int i = 1;i <= n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
}
