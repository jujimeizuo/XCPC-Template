const int N = 1e5 + 10;
vector<int> g[N];

int fa[N][30];
int dep[N];

void dfs(int u, int par) {
    dep[u] = dep[fa[u][0] = par] + 1;
    for(int i = 1;i <= 20; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(auto v : g[u]) {
        if(v == par) continue;
        dfs(v, u);
    }
}

int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 20;i >= 0; i--) {
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if(x == y) return x;
    for(int i = 20;i >= 0; i--) {
        if(fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}