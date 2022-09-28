template <typename T>
bool isBipartiteGraph(const graph<T>& g) {
    std::vector<int> color(g.n);
    bool flag = true;
    std::function<bool(int, int)> dfs = [&](int u, int x) -> bool {
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (!color[to]) {
                dfs(to, 3 - x);
            }
            if (color[to] == color[u]) {
                flag = false;
            }
        }
    };
    for (int i = 0; i < g.n; i++) {
        if (!color[i]) {
            dfs(i, 1);
        }
    }
    return flag;
}