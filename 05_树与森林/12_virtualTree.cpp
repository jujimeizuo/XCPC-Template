//虚树可以处理多次询问, 并且每次询问只需要树上的K个关键点
//建立的虚树能保证点数 < 2 * K
//如果对虚树做dp, 总体复杂度和∑K有关
//考虑dp的时候, 需要同时考虑非关键点对答案的影响

int n;

struct edge {
    int nxt, to;
} e[N << 1];
int head[N], tot;
void add(int u, int v) { e[++tot] = edge{ head[u], v }, head[u] = tot;}

int dep[N], fa[N], topfa[N], siz[N], son[N], dfn[N], cnt;
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    int max_son = -1;
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != par) {
            dfs(v, u);
            siz[u] += siz[v];
            if (max_son < siz[v]) son[u] = v, max_son = siz[v];
        }
}
void dfs2(int u, int topf) {
    topfa[u] = topf, dfn[u] = ++cnt;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}
int LCA(int x, int y) {
    while (topfa[x] != topfa[y]) {
        if (dep[topfa[x]] < dep[topfa[y]]) swap(x, y);
        x = fa[topfa[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int getDis(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)]; }

//建立虚树
int tag[N];//tag[u] = 1 <=> 关键点
vector<int> g[N];//虚树边
void add_edge(int u, int v) { g[u].push_back(v); }
int st[N], top, rt;//rt为虚树根
void insert(int u) {
    if (top == 1) {
        st[++top] = u;
        return;
    }
    int lca = LCA(u, st[top]);
    if (lca != st[top]) {
        while (top > 1 && dfn[st[top - 1]] >= dfn[lca])
            add_edge(st[top - 1], st[top]), top--;
        if (lca != st[top]) add_edge(lca, st[top]), st[top] = lca;
    }
    st[++top] = u;
}
bool cmp(const int &x, const int &y) { return dfn[x] < dfn[y]; }
void build(vector<int> &v) {
    st[top = 1] = rt;
    sort(v.begin(), v.end(), cmp);
    for (auto &i: v) {
        tag[i] = 1;
        if (i != rt) insert(i);
    }
    while (top > 1) add_edge(st[top - 1], st[top]), top--;
}


void dp(int u) {
    //...
}
void clear(int u) {//清空虚树边和标记, 也可以和dp合并
    for (auto &v: g[u]) clear(v);
    g[u].clear(); tag[u] = 0;
}
void solve() {
    //...
    dp(rt); clear(rt);
    //...
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
    }
    //此处距离为1, 所以用dep替代dis, dis[fa[rt] = 0] = -1
    dep[0] = -1, rt = 1;
    dfs(rt, 0); dfs2(rt, rt);


    int Q; scanf("%d", &Q);
    while (Q--) {
        int K; scanf("%d", &K);//读取关键点
        for (int i = 1; i <= K; i++) scanf("%d", &a[i]);
        //构建虚树
        build(a);
        solve();
    }

    return 0;
}