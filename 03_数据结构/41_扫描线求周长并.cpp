// 纵向扫描
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

#define INF 0x3fffff
#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) >> 1

int n;

struct L {
    int y, x1, x2;
    int state;
    bool operator < (L rhs) {return y < rhs.y; }
}line[N << 2];

struct Node {
    int l, r, cover;
    bool ls, rs;
    int num;
    int len;
}t[N << 2];

inline void push_up(int u) {
    if(t[u].cover) {
        t[u].len = t[u].r - t[u].l + 1;
        t[u].ls = t[u].rs = 1;
        t[u].num = 1;
    }
    else if(t[u].l == t[u].r) {
        t[u].ls = t[u].rs = 0;
        t[u].len = t[u].num = 0;
    }
    else {
        t[u].len = t[lc].len + t[rc].len;
        t[u].ls = t[lc].ls; t[u].rs = t[rc].rs;
        t[u].num = t[lc].num + t[rc].num - (t[lc].rs & t[rc].ls);
    }
}

void build(int u, int l, int r) {
    t[u].l = l; t[u].r = r;
    if(l == r) {
        t[u].len = t[u].cover = t[u].ls = t[u].rs = t[u].num = 0;
        return ;
    }
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
}

void modify(int u, int ql, int qr, int state) {
    if(ql <= t[u].l && t[u].r <= qr) {
        t[u].cover += state;
        push_up(u);
        return ;
    }
    if(ql <= mid) modify(lc, ql, qr, state);
    if(qr > mid)  modify(rc, ql, qr, state);
    push_up(u);
}

void init() {
    cin >> n;
    int mx = -INF, mn = INF;
    for (int i = 1; i <= n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        mx = max(mx, max(x1, x2));
        mn = min(mn, min(x1, x2));
        line[i] = L{y1, x1, x2, 1};
        line[n + i] = L{y2, x1, x2, -1};
    }
    n <<= 1;
    sort(line + 1, line + n + 1);
    build(1, mn, mx);
}

void solve() {
    int ans = 0;
    int last = 0;
    for(int i = 1;i <= n; i++) {
        modify(1, line[i].x1, line[i].x2 - 1, line[i].state);
        ans += abs(t[1].len - last); // 横线
        ans += (line[i + 1].y - line[i].y) * 2 * t[1].num; // 竖线
        last = t[1].len;
    }
    printf("%d\n",ans);
}

int main() {
    init();
    solve();
}
