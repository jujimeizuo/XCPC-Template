//问题可以莫队（询问可以离线，不带修改）
//区间伸长的时候很好维护信息
//区间缩短的时候不太好维护信息（如最大值，删除以后不知道次大值是多少)
// O(nsqrt(n))

struct Hash {
    int b[N], tot;
    void init() { tot = 0; }
    void insert(int x) { b[++tot] = x; }
    void build() {
        sort(b + 1, b + 1 + tot);
        tot = unique(b + 1, b + 1 + tot) - (b + 1);
    }
    int pos(int x) { return lower_bound(b + 1, b + 1 + tot, x) - b; }
} ha;

int n, m;
int c[N], pos[N], cnt[N], cntt[N];
int belong[N], sizz;
ll ans[N], res;

struct Query {
    int l, r, id;
    bool operator < (const Query &rhs) const {
        return belong[l] ^ belong[rhs.l] ? belong[l] < belong[rhs.l] : r < rhs.r;
    }
} q[N];

ll bruteForce(int ql, int qr) {
    ll result = 0;
    for (int i = ql; i <= qr; i++) {
        cntt[pos[i]]++;
        result = max(result, 1ll * c[i] * cntt[pos[i]]);
    }
    for (int i = ql; i <= qr; i++) cntt[pos[i]]--;
    return result;
}

void add(int x) {
    cnt[pos[x]]++;
    res = max(res, 1ll * c[x] * cnt[pos[x]]);
}

void del(int x) {
    cnt[pos[x]]--;
}

int main() {


    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]), ha.insert(c[i]);
    ha.build();
    for (int i = 1; i <= n; i++) pos[i] = ha.pos(c[i]);

    sizz = sqrt(n); int num = ceil((long double)n / sizz);
    for (int i = 1, j = 1; i <= num; i++)
        while (j <= i * sizz && j <= n)
            belong[j++] = i;

    for (int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + m);

    for (int i = 1, j = 1; i <= num; i++) {
        memset(cnt, 0, sizeof(cnt));
        int right = min(i * sizz, n);
        res = 0;
        for (int l = right + 1, r = right; j <= m && belong[q[j].l] == i; j++, l = right + 1) {
            int ql = q[j].l, qr = q[j].r;
            if (qr - ql + 1 <= sizz) {
                ans[q[j].id] = bruteForce(ql, qr);
                continue;
            }
            while (r < qr) add(++r);
            ll tmp = res;
            while (l > ql) add(--l);
            ans[q[j].id] = res;
            res = tmp;
            while (l < right + 1) del(l++);
        }
    }

    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);

    return 0;
}
