//带修莫队模板题
//查询[ql, qr]间不同颜色数量，带修改

// O(n^{5/3})

int n, m;
int c[N], cnt[N];
int belong[N], size, totq, totm;
int ans[N], res;

struct Query {
    int l, r, t, id;
    bool operator < (const Query &rhs) const {
        return belong[l] ^ belong[rhs.l] ? belong[l] < belong[rhs.l] :
               (belong[r] ^ belong[rhs.r] ? belong[r] < belong[rhs.r] : t < rhs.t);
    }
} q[N];

struct Modify {
    int pos, val;
} modify[N];

void add(int x) {
    if (!cnt[c[x]]) res++;
    cnt[c[x]]++;
}

void del(int x) {
    cnt[c[x]]--;
    if (!cnt[c[x]]) res--;
}

void upd(int x, int ql, int qr) {
    int pos = modify[x].pos;
    if (ql <= pos && pos <= qr) {
        cnt[c[pos]]--; if (!cnt[c[pos]]) res--;
        if (!cnt[modify[x].val]) res++; cnt[modify[x].val]++;
    }
    swap(modify[x].val, c[pos]);//��θĵ����´λ�Ļ�ȥ
}

int main() {
#ifdef ACM_LOCAL
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= m; i++) {
        char op[10]; scanf("%s", op);
        if (op[0] == 'Q') {
            int ql, qr; scanf("%d%d", &ql, &qr); totq++;
            q[totq] = Query{ql, qr, totm, totq};
        }
        else {
            int pos, val; scanf("%d%d", &pos, &val); totm++;
            modify[totm] = Modify{pos, val};
        }
    }

    //size = N ^ (2 / 3), (N * totm) ^ (1 / 3)
    size = ceil(pow(n, (long double)2.0 / 3)); int num = ceil((long double)n / size);
    for (int i = 1, j = 1; i <= num; i++)
        while (j <= i * size && j <= n)
            belong[j++] = i;

    sort(q + 1, q + 1 + totq);

    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= totq; i++) {
        int ql = q[i].l, qr = q[i].r, qt = q[i].t;
        while (l < ql) del(l++);
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (r > qr) del(r--);
        while (t < qt) upd(++t, ql, qr);
        while (t > qt) upd(t--, ql, qr);
        ans[q[i].id] = res;
    }

    for (int i = 1; i <= totq; i++) printf("%d\n", ans[i]);

    return 0;
}
