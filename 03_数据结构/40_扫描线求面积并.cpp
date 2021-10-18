// 横向扫描
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) >> 1

int n, cnt;

double v[N];
struct L {
    double x, y1, y2;
    int state;
    bool operator < (L rhs) {return x < rhs.x; }
}line[N << 2];

struct Node {
    int l, r, cover;
    double len;
}t[N << 2];

inline void push_up(int u) {
    if(t[u].cover) t[u].len = v[t[u].r + 1] - v[t[u].l];
    else if(t[u].l == t[u].r) t[u].len = 0;
    else t[u].len = t[lc].len + t[rc].len;
}

void build(int u, int l, int r) {
    t[u].l = l; t[u].r = r;
    if(l == r) {
        t[l].cover = t[l].len = 0;
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
    for(int i = 1;i <= n; i++) {
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        line[i] = L{x1, y1, y2, 1}; v[i] = y1;
        line[n + i] = L{x2, y1, y2, -1}; v[n + i] = y2;
    }
    n <<= 1;
    sort(line + 1, line + n + 1);
    sort(v + 1, v + n + 1);
    cnt = unique(v + 1, v + n + 1) - (v + 1);
    build(1, 1, cnt);
}

void solve() {
    double ans = 0;
    for(int i = 1;i <= n; i++) {
        int ql = lower_bound(v + 1, v + cnt + 1, line[i].y1) - v;
        int qr = lower_bound(v + 1, v + cnt + 1, line[i].y2) - v - 1;
        modify(1, ql, qr, line[i].state);
        ans += t[1].len * (line[i + 1].x - line[i].x);
    }
    cout << ans << endl;
}

int main() {
    init();
    solve();
}
