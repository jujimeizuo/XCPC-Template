const int N = 1e5 + 10;

#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) / 2

struct Tree {
    int l, r;
    int sum, tag;
}t[N << 1];

void push_up(int u) {
    t[u].sum = t[lc].sum + t[rc].sum;
}

void push_down(int u) {
    if(!t[u].tag) return ;
    t[lc].sum += t[u].tag * (t[lc].r - t[lc].l + 1);
    t[rc].sum += t[u].tag * (t[rc].r - t[rc].l + 1);
    t[lc].tag += t[u].tag;
    t[rc].tag += t[u].tag;
    t[u].tag = 0;
}

void modify(int u, int ql, int qr, int v) {
    if(ql <= t[u].l && t[u].r <= qr) return ;
    push_down(u);
    if(ql <= mid) modify(lc, ql, qr, v);
    if(qr > mid)  modify(rc, ql, qr, v);
    push_up(u);
}

int query(int u, int ql, int qr) {
    if(ql <= t[u].l && t[u].r <= qr) return t[u].sum;
    push_down(u);
    int ans = 0;
    if(ql <= mid) ans += query(lc, ql, qr);
    if(qr > mid)  ans += query(rc, ql, qr);
    return ans;
}
