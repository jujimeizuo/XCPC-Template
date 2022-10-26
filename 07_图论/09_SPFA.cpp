template <typename T>
std::vector<T> spfa(const graph<T>& g, int st) {
    std::vector<T> dist(g.n, std::numeric_limits<T>::max());
    std::vector<bool> vis(g.n);
    std::vector<int> cnt(g.n);
    std::vector<int> x(1, st);
    dist[st] = 0; vis[st] = true;
    for (int ptr = 0; ptr < x.size(); ptr++) {
        int u = x[ptr];
        vis[u] = false;
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (dist[to] > dist[u] + e.cost) {
                dist[to] = dist[u] + e.cost;
                if (!vis[to]) {
                    cnt[to]++;
                    vis[to] = true;
                    if (cnt[to] >= g.n) {
                        return std::vector<T>();
                    }
                    x.push_back(to);
                }
            }
        }
    }
    return dist;
}