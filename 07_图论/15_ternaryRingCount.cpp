template <typename T>
int ternaryRingCount(const digraph<T>& g) {
    std::vector<int> d(g.n);
    for (auto& e : g.edges) {
        int from = e.from, to = e.to;
        d[from]++;
        d[to]++;
    }
    digraph<T>& ng(g.n);
    for (auto& e : g.edges) {
        int from = e.from, to = e.to;
        if (d[from] < d[to] || (d[from] == d[to] && from > to)) std::swap(from, to);
        ng.add(from, to);
    }
    int ans = 0;
    std::vector<bool> was(ng.n);
    for (int u = 0; u < ng.n; u++) {
        for (int id : ng.g[u]) {
            auto& e = ng.edges[id];
            int to = e.to;
            was[to] = u;
        }
        for (int id1 : ng.g[u]) {
            auto& e1 = ng.edges[id1];
            int to1 = e1.to;
            for (int id2 : ng.g[to1]) {
                auto& e2 = ng.g[id2];
                int to2 = e2.to;
                if (was[to2] == u) ans++;
            }
        }
    }
    return ans;
}