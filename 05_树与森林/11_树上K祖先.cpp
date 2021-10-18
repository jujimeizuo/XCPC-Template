//倍增KFA, 空间大点, 但是好写
vector<int> g[N];

int anc[N][20];
void dfs(int u, int fa) {
    anc[u][0] = fa;
    for (int i = 1; i <= 19; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (auto &v: g[u])
        if (v != fa) dfs(v, u);
}

int kthFa(int u, int k) {
    int bit = 0;
    while (k) {
        if (k & 1) u = anc[u][bit];
        k >>= 1;
        bit++;
    }
    return u;
}


//树剖KFA
int siz[N], son[N], dep[N], fa[N], top[N];
int id[N], nodeOf[N], cnt;
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    for (auto &v: g[u])
        if (v != par) {
            dfs(v, u);
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]])
                son[u] = v;
        }
}

void dfs2(int u, int topf) {
    nodeOf[id[u] = ++cnt] = u, top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto &v: g[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

int kthFa(int u, int k) {
    while (k >= id[u] - id[top[u]] + 1 && u) {
        k -= id[u] - id[top[u]] + 1;
        u = fa[top[u]];
    }
    return nodeOf[id[u] - k];
}