const int maxn = 4e5 + 10;

struct Edge {
    int v, next;
}e[maxn << 1];

int head[maxn * 2], cnt;

inline void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
 
int fa[maxn], dep[maxn], siz[maxn], son[maxn];

void dfs1(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    for(int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].v;
        if(v == par) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(!son[u] || siz[v] > siz[son[u]]) 
            son[u] = v;
    }
}

int dfn[maxn], top[maxn], nodeof[maxn], tim;

void dfs2(int u, int topf) {
    nodeof[dfn[u] = ++tim] = u;
    top[u] = topf;
    if(!son[u]) return ;
    dfs2(son[u], topf);
    for(int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].v;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int w[maxn];

#define lc u << 1
#define rc u << 1 | 1
#define mid (t[u].l + t[u].r) / 2
struct Tree {
    int l, r, sum, tag;
}t[maxn << 2];
inline void push_up(int u) ;
inline void push_down(int u) ;
void build(int u, int l, int r) ;
void modify(int u, int ql, int qr, int v) ;
int query(int u, int ql, int qr) ;

void modify_chain(int x, int y, int val) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        modify(1, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    modify(1, dfn[x], dfn[y], val);
}

int query_chain(int x, int y) {
    int ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += query(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    ans += query(1, dfn[x], dfn[y]);
    return ans;
}

signed main() {
    memset(head, -1, sizeof(head));
    int n; cin >> n;
    for(int i = 1;i <= n; i++) cin >> w[i];
    for(int i = 1;i <= n - 1; i++) {
        int u, v; cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    int m; cin >> m;
    while(m--) {
        int opt; cin >> opt;
        if(opt == 1) {
            int x, y, val; cin >> x >> y >> val;
            modify_chain(x, y, val);
        }
        else if(opt == 2) {
            int x, val; cin >> x >> val;
            modify(1, dfn[x], dfn[x] + siz[x] - 1, val);
        }
        else if(opt == 3) {
            int x, y; cin >> x >> y;
            cout << query_chain(x, y) << endl;
        }
        else if(opt == 4) {
            int x; cin >> x;
            cout << query(1, dfn[x], dfn[x] + siz[x] - 1) << endl;
        }
    }
}