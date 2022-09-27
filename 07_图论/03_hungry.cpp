template <typename T>
int hungry(const digraph<T>& g) {
    std::vector<bool> was(g.n);
    std::vector<int> match(g.n, -1);
    std::function<bool(int)> dfs = [&](int u) -> bool {
        for (int id : g.g[u]) {
            auto& e : g.edges[id];
            int to = e.to;
            if (!was[to]) {
                was[to] = true;
                if (match[to] == -1 || dfs(match[to])) {
                    match[to] = u;
                    return true;
                }
            }
        }
        return false;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        vis.assign(g.n, false);
        if (dfs(i)) ans++;
    }
    return ans;
}