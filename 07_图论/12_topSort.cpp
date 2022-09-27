template <typename T>
std::vector<int> find_topsort(const digraph<T> &g) {
    std::vector<int> deg(g.n, 0);
    for (int id = 0; id < (int) g.edges.size(); id++) {
        deg[g.edges[id].to]++;
    }
    std::vector<int> x;
    for (int i = 0; i < g.n; i++) {
        if (deg[i] == 0) {
            x.push_back(i);
        }
    }

    for (int ptr = 0; ptr < (int) x.size(); ptr++) {
        int i = x[ptr];
        for (int id : g.g[i]) {
            auto &e = g.edges[id];
            int to = e.to;
            if (--deg[to] == 0) {
                x.push_back(to);
            }
        }
    }

    if ((int) x.size() != g.n) {
        return std::vector<int>();
    }
    return x;
}

