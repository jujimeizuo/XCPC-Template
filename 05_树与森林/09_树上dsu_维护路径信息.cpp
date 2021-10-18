const int N = 1e5 + 10;

vector<int> g[N];
int siz[N], dep[N], son[N], dfn[N], nodeof[N], tim;

void calc(int u, int w) {
    // ....对u这一节点进行单独处理
    if(w > 0) // ....计算贡献
    else // ....撤销影响
}

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + (siz[u] = 1);
    nodeof[dfn[u] = ++tim] = u;
    for(auto v : g[u]) {
        if(v == fa) continue ;
        dfs1(v, u);
        siz[u] += siz[v];
        if(!son[u] || siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fa, bool keep) {
    for(auto v : g[u]) {
        if(v == fa || v == son[u]) continue ;
        dfs2(v, u, 0);
    }
    if(son[u]) {
        dfs2(son[u], u, 1);
    }
    for(auto v : g[u]) {
        if(v == fa || v == son[u]) continue ;
        for(int j = 0;j < siz[v]; j++) {
            // ....更新答案
        }
        for(int j = 0;j < siz[v]; j++) {
            calc(nodeof[dfn[v] + j], 1);
        }
    }
    calc(u, 1);
    // ....更新答案
    if(!keep) {
        for(int i = 0;i < siz[u]; i++) calc(nodeof[dfn[u] + i], -1);
    }
}

int main() {
    int n; cin >> n;
    for(int i = 1;i < n; i++) {
        int u, v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0, 0);
}