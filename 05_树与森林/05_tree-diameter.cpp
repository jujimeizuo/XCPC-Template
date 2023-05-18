template <typename T>
std::vector<int> find_tree_diameter(const forest<T>& g, T& diameter) {
    diameter = 0;
    int st = 0, ed = 0;
    std::vector<T> dis(g.n);
    std::vector<int> pre(g.n);

    std::function<void(int, int)> dfs1 = [&](int u, int parent) {
        if (dis[u] > dis[st]) st = u;
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (to == parent) continue ;
            dis[to] = dis[u] + e.cost;
            dfs1(to, u);
        }
    };

    std::function<void(int, int)> dfs2 = [&](int u, int parent) {
        if (dis[u] > dis[ed]) ed = u;
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (to == parent) continue ;
            pre[to] = u;
            dis[to] = dis[u] + e.cost;
            dfs2(to, u);
        }
    };

    dfs1(0, -1);
    dis.assign(g.n, 0);
    dfs2(st, -1);
    std::vector<int> vertexs{ed};
    int now = ed;
    do {
        vertexs.push_back(pre[now]);
        now = pre[now];
    } while (now != st);
    reverse(vertexs.begin(), vertexs.end());
    return vertexs;
}

template <typename T>
std::vector<int> find_tree_all_diameters(const forest<T>& g, T& diameter) {
    diameter = 0;
    std::vector<std::array<T, 2>> dp(g.n);
    std::vector<int> down(g.n);
    std::vector<T> up(g.n);

    std::function<void(int, int)> dfs1 = [&](int u, int parent) {
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (to == parent) continue ;
            dfs1(to, u);
            if (dp[to][0] + e.cost > dp[u][0]) {
                dp[u][1] = dp[u][0];
                dp[u][0] = dp[to][0] + e.cost;
                down[u] = to;
            } else if (dp[to][0] + e.cost > dp[u][1]) {
                dp[u][1] = dp[to][0] + e.cost;
            }
            diameter = std::max(diameter, dp[u][1] + dp[u][0]);
        }
    };

    std::function<void(int, int)> dfs2 = [&](int u, int parent) {
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (to == parent) continue;
            up[to] = up[u] + e.cost;
            if (down[u] == to) up[to] = std::max(up[to], dp[u][1] + e.cost);
            else up[to] = std::max(up[to], dp[u][0] + e.cost);
            dfs2(to, u);
        }
    };

    dfs1(0, -1);
    dfs2(0, -1);
    std::vector<int> vertexs;
    for (int i = 0; i < g.n; i++) {
        std::vector<int> dis{ dp[i][1], dp[i][0], up[i] };
        sort(dis.begin(), dis.end());
        if (dis[1] + dis[2] == diameter) vertexs.push_back(i);
    }
    return vertexs;
};
