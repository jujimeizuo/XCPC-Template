#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

struct Node {
    int l, r, val;
}hjt[N * 40 * 2];

int cnt, rootfa[N], rootdep[N], tot;
int n;

inline void build(int &now, int l, int r) {
    now = ++cnt;
    if(l == r) {
        hjt[now].val = ++tot;
        return ;
    }
    int m = (l + r) >> 1;
    build(hjt[now].l, l, m);
    build(hjt[now].r, m + 1, r);
}

inline void modify(int ver, int &now, int l, int r, int pos, int value) {
    hjt[now = ++cnt] = hjt[ver];
    if(l == r) {
        hjt[now].val = value;
        return ;
    }
    int m = (l + r) >> 1;
    if(pos <= m) modify(hjt[ver].l, hjt[now].l, l, m, pos, value);
    else modify(hjt[ver].r, hjt[now].r, m + 1, r, pos, value);
}

inline int query(int now, int l, int r, int pos) {
    if(l == r) return hjt[now].val;
    int m = (l + r) >> 1;
    if(pos <= m) return query(hjt[now].l, l, m, pos);
    else return query(hjt[now].r, m + 1, r, pos);
}

inline int find(int ver, int x) {
    int fx = query(rootfa[ver], 1, n, x);
    return fx == x ? x : find(ver, fx);
}

inline void merge(int ver, int x, int y) {
    x = find(ver - 1, x);
    y = find(ver - 1, y);
    if(x == y) {
        rootfa[ver] = rootfa[ver - 1];
        rootdep[ver] = rootdep[ver - 1];
    }
    else {
        int depx = query(rootdep[ver - 1], 1, n, x);
        int depy = query(rootdep[ver - 1], 1, n, y);
        if(depx < depy) {
            modify(rootfa[ver - 1], rootfa[ver], 1, n, x, y);
            rootdep[ver] = rootdep[ver - 1];
        }
        else if(depx > depy) {
            modify(rootfa[ver - 1], rootfa[ver], 1, n, y, x);
            rootdep[ver] = rootdep[ver - 1];
        }
        else {
            modify(rootfa[ver - 1], rootfa[ver], 1, n, x, y);
            modify(rootdep[ver - 1], rootdep[ver], 1, n, y, depy + 1);
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    build(rootfa[0], 1, n);
    for(int ver = 1;ver <= m; ver++) {
        int opt, x, y;
        cin >> opt;
        if(opt == 1) {
            cin >> x >> y;
            merge(ver, x, y);
        }
        else if(opt == 2) {
            cin >> x;
            rootfa[ver] = rootfa[x];
            rootdep[ver] = rootdep[x];
        }
        else {
            cin >> x >> y;
            rootfa[ver] = rootfa[ver - 1];
            rootdep[ver] = rootdep[ver - 1];
            int u = find(ver, x);
            int v = find(ver, y);
            if(u == v) cout << 1 << endl;
            else cout << 0 << endl;
        }
    }
}
