#include <bits/stdc++.h>
using namespace std;

const int MAX = 4e5 + 10;
int n;

struct Splay {
#define rt  ch[0][1]
#define lc  ch[u][0]
#define rc  ch[u][1]
    int tot, totElement;
    int val[MAX], fa[MAX], sum[MAX], tag[MAX];
    int ch[MAX][2];
    Splay() { tot = totElement = 0; }
    void push_up(int u) { sum[u] = sum[lc] + sum[rc] + 1; }
    void push_down(int u) {
        if (tag[u]) {
            tag[lc] ^= 1;
            tag[rc] ^= 1;
            tag[u] = 0;
            swap(lc, rc);
        }
    }
    int identify(int u) { return ch[fa[u]][1] == u; }
    void connect(int u, int par, int son) { ch[par][son] = u, fa[u] = par; }
    void rotate(int u) {
        int fc = identify(u), f = fa[u];
        int gc = identify(f), g = fa[f];
        int uc = fc ^ 1, son = ch[u][uc];
        connect(son, f, fc);
        connect(f, u, uc);
        connect(u, g, gc);
        push_up(f);
        push_up(u);
    }
    void splay(int u, int v) {
        v = fa[v];
        while (fa[u] != v) {
            int f = fa[u];
            if (fa[f] != v)
                rotate(identify(u) ^ identify(f) ? u : f);
            rotate(u);
        }
    }
    int creat(int v, int par) {
        val[++tot] = v;
        fa[tot] = par;
        sum[tot] = 1;
        return tot;
    }
    int insert(int v) {
        totElement++;
        if (totElement == 1) {
            creat(v, 0);
            return rt = tot;
        }
        int u = rt;
        while (1) {
            sum[u]++;
            if (v == val[u]) return u;
            int nxt = v > val[u];
            if (!ch[u][nxt]) {
                creat(v, u);
                splay(ch[u][nxt] = tot, rt);
                return tot;
            }
            u = ch[u][nxt];
        }
    }
    int queryKth(int k) {
        if (k > totElement) return -1;
        int u = rt;
        while (1) {
            push_down(u);
            if (k > sum[lc] && k <= sum[lc] + 1) {
                splay(u, rt);
                return val[u];
            }
            if (k <= sum[lc]) u = lc;
            else {
                k -= sum[lc] + 1;
                u = rc;
            }
        }
    }
    void reverse(int ql, int qr) {
        ql = queryKth(ql);
        qr = queryKth(qr + 2);
        splay(ql, rt);
        splay(qr, ch[ql][1]);
        tag[ch[qr][0]] ^= 1;
    }
    void DFS(int u) {
        push_down(u);
        if(lc) DFS(lc);
        if(val[u] > 1 && val[u] < n + 2)
            cout << val[u] - 1 << " ";
        if(rc) DFS(rc);
    }
} splay;

void solve() {
    int m; cin >> n >> m;
    for(int i = 1;i <= n + 2; i++) splay.insert(i);
    while(m--) {
        int l, r; cin >> l >> r;
        splay.reverse(l, r);
    }
    splay.DFS(splay.ch[0][1]);
    cout << endl;
}

/*--------------------------*/

typedef long long ll;

#define INF 0x3f3f3f3f

const int N = 1e5 + 10;

int a[N];
int n, cnt, root;

struct Node {
    int ch[2];
    int val, fa;
    int siz, tag;
} t[N];

void update(int x) {
    t[x].siz = t[t[x].ch[0]].siz + t[t[x].ch[1]].siz + 1;
}

void push_down(int x) {
    if (x && t[x].tag) {
        t[t[x].ch[0]].tag ^= 1;
        t[t[x].ch[1]].tag ^= 1;
        swap(t[x].ch[0], t[x].ch[1]);
        t[x].tag = 0;
    }
}

int id(int x) {
    return x == t[t[x].fa].ch[1];
}

void connect(int fa, int x, int d) {
    t[x].fa = fa;
    t[fa].ch[d] = x;
}

void rotate(int x) {
    int f = t[x].fa;
    int ff = t[f].fa;
    push_down(x);
    push_down(f);
    int fson = id(x);
    int ffson = id(f);
    int son = t[x].ch[fson ^ 1];
    connect(f, son, fson);
    connect(x, f, fson ^ 1);
    connect(ff, x, ffson);
    update(f), update(x);
}

void splay(int x, int to) { // 将 x 转到 to 的子节点位置
    while (t[x].fa != to) {
        int f = t[x].fa;
        if (t[f].fa != to) {
            rotate(id(x) == id(f) ? f : x);
        }
        rotate(x);
    }
    if (!to) { // 在 splay(l, 0) 时起作用
        root = x;
    }
}

int build(int l, int r, int fa) {
    if (l > r) {
        return 0;
    }
    int mid = (l + r) >> 1;
    int x = ++cnt;
    t[x].fa = fa;
    t[x].siz = 1;
    t[x].val = a[mid];
    t[x].ch[0] = build(l, mid - 1, x);
    t[x].ch[1] = build(mid + 1, r, x);
    update(x);
    return x;
}

int find(int rank) {
    int x = root;
    while (1) {
        push_down(x);
        if (rank <= t[t[x].ch[0]].siz) {
            x = t[x].ch[0];
        } else {
            rank -= t[t[x].ch[0]].siz + 1;
            if (!rank) {
                return x;
            }
            x = t[x].ch[1];
        }
    }
}

void reverse(int l, int r) {
    l = find(l);
    r = find(r);
    splay(l, 0);
    splay(r, l);
    int pos = t[t[root].ch[1]].ch[0];
    t[pos].tag ^= 1;
}

void print(int x) {
    if (!x) {
        return;
    }
    push_down(x);
    print(t[x].ch[0]);
    if (t[x].val != INF && t[x].val != -INF) {
        printf("%d ", t[x].val);
    }
    print(t[x].ch[1]);
}

void solve() {
    cin >> n >> m;
    for(int i = 1;i <= n; i++) cin >> a[i + 1];
    a[1] = -INF; a[n + 2] = INF;
    root = build(1, n + 2, 0);
    for(int i = 1;i <= m; i++) {
        int l, r; cin >> l >> r;
        reverse(l + 1, r + 1);
    }
    print(root);
}