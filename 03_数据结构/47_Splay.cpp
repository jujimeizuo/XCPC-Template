#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

struct Splay { // 有旋平衡树
#define rt  ch[0][1]
#define lc  ch[u][0]
#define rc  ch[u][1]
#define identify(u) (ch[fa[u]][1] == u)
    int tot, totElement;
    int val[N], cnt[N], fa[N], sum[N];
    int ch[N][2];
    Splay() { tot = totElement = 0; }
    void push_up(int u) { sum[u] = sum[lc] + sum[rc] + cnt[u]; }
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
        sum[tot] = cnt[tot] = 1;
        return tot;
    }
    void destory(int u) {
        val[u] = cnt[u] = fa[u] = sum[u] = lc = rc = 0;
        tot -= u == tot;
    }
    int find(int v) {
        int u = rt;
        while (1) {
            if (val[u] == v) {
                splay(u, rt);
                return u;
            }
            int nxt = v > val[u];
            if (!ch[u][nxt]) return -1;
            u = ch[u][nxt];
        }
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
            if (v == val[u]) {
                cnt[u]++;
                return u;
            }
            int nxt = v > val[u];
            if (!ch[u][nxt]) {
                creat(v, u);
                splay(ch[u][nxt] = tot, rt);
                return tot;
            }
            u = ch[u][nxt];
        }
    }
    void remove(int v) {
        int u = find(v);
        if (!u) return;
        totElement--;
        if (cnt[u] > 1) {
            cnt[u]--, sum[u]--;
            return;
        }
        if (!lc) fa[rt = rc] = 0;
        else {
            int now = lc;
            while (ch[now][1]) now = ch[now][1];
            splay(now, lc);
            connect(rc, now, 1); connect(now, 0, 1);
            push_up(now);
        }
        destory(u);
    }
    int getRank(int v) {
        int k = 0, u = rt;
        while (1) {
            if (v == val[u]) {
                k += sum[lc] + 1;
                splay(u, rt);
                return k;
            }
            else if (v < val[u]) u = lc;
            else {
                k += sum[lc] + cnt[u];
                u = rc;
            }
            if (!u) return 0;
        }
    }
    int atRank(int k) {
        if (k > totElement) return -1;
        int u = rt;
        while (1) {
            if (k > sum[lc] && k <= sum[lc] + cnt[u]) {
                splay(u, rt);
                break;
            }
            if (k <= sum[lc]) u = lc;
            else {
                k -= sum[lc] + cnt[u];
                u = rc;
            }
        }
        return val[u];
    }
    int upper(int v) {
        int u = rt, minn = 0x3f3f3f3f, p = 0;
        while (u) {
            if (val[u] > v && val[u] < minn) minn = val[u], p = u;
            if (v >= val[u]) u = rc;
            else u = lc;
        }
        if (!p) splay(p, rt);
        return minn;
    }
    int lower(int v) {
        int u = rt, maxx = -0x3f3f3f3f, p = 0;
        while (u) {
            if (val[u] < v && val[u] > maxx) maxx = val[u], p = u;
            if (v <= val[u]) u = lc;
            else u = rc;
        }
        if (!p) splay(p, rt);
        return maxx;
    }
}splay;

void solve() {
    int _; cin >> _;
    while(_--) {
        int opt, x;
        cin >> opt >> x;
        if(opt == 1) splay.insert(x);
        else if(opt == 2) splay.remove(x);
        else if(opt == 3) cout << splay.getRank(x) << endl;
        else if(opt == 4) cout << splay.atRank(x) << endl;
        else if(opt == 5) cout << splay.lower(x) << endl;
        else if(opt == 6) cout << splay.upper(x) << endl;
    }
}