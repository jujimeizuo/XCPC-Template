template <typename T>
bool find_mst(const undigraph<T> &g, T& ans) {
    std::vector<bool> vis(g.n);
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>> > q;
    q.push({0, 0});
    int cnt = 0; ans = 0;
    while (!q.empty() && cnt < g.n) {
        T expected = q.top().first;
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ans += expected; cnt++;
        for (int id : g.g[u]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (!vis[to]) {
                q.push({e.cost, to});
            }
        }
    }
    return cnt == g.n;
    // returns false if there's not connected
}