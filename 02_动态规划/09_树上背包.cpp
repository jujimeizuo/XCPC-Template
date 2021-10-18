//加了剪枝后复杂度为O(NM)

void dfs(int u, int fa) {
    siz[u] = 1;
    for (auto &v: g[u])
        if (v != fa) {
            dfs(v, u);

            int now = min(siz[u] + siz[v] + 1, M);
            int t[MAX_M]; for (int i = 0; i <= M; i++) t[i] = INF/-INF;//初始化
            for (int i = 0; i <= siz[u]; i++)
                for (int j = 0; j <= siz[v] && i + j <= M; j++) {
                    //...转移方程
                }
            for (int i = 0; i <= now; i++) f[u][i] = min/max(f[u][i], t[i]);
            siz[u] = now;
        }
}
