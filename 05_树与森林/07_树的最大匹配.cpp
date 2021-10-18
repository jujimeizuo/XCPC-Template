// 设状态为f[u][1/0]表示以u为根的子树与儿子连边/不连边的最大匹配

const int N = 1e5 + 10;
vector<int> g[N];
int f[N][2];

void dfs(int u, int fa) {
    int mn = INF;
    for(auto v : g[u]) {
        if(v == fa) continue ;
        dfs(v, u);
        f[u][0] += f[v][1]; // u不与儿子连边，即加上所有与儿子连边的v
        f[u][1] += f[v][1]; // u与儿子连边，即加上一个不与儿子连边的v和其他所有与儿子连边的v
        mn = min(mx, f[v][1] - f[v][0]);
    }
    if(mn != INF) f[u][1] = dp[u][1] - mx + 1;
}
