template <typename T>
T treeKnapSack(const forest<T>& g) {
    std::vector<int> siz(n);
    std::vector<std::vector<T>> dp(n);

    std::function<void(int, int)> dfs = [&](int u, int fa) {
        siz[u] = 1;
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (to == fa) continue ;
            dfs(to, u);
            int now = min(siz[u] + siz[v] + 1, M);
            int t[MAX_M]; for (int i = 0; i <= M; i++) t[i] = INF/-INF;//初始化
            for (int i = 0; i <= siz[u]; i++)
                for (int j = 0; j <= siz[v] && i + j <= M; j++) {
                    //...转移方程
                }
            for (int i = 0; i <= now; i++) f[u][i] = min/max(f[u][i], t[i]);
            siz[u] = now;
        }
    };
} 
