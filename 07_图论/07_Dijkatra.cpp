template <typename T>
std::vector<T> dijkstra(const graph<T>& g, int st) {
    assert(0 <= st && st < g.n);
    std::vector<T> dist(g.n, std::numeric_limits<T>::max());
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>> > q;
    dist[st] = 0;
    q.emplace(dist[st], st);
    while (!q.empty()) {
        T expected = q.top().first;
        int u = q.top().second; q.pop();
        if (dist[u] != expected) {
            continue ;
        }
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ u;
            if (dist[to] > dist[e.from] + e.cost) {
                dist[to] = dist[e.from] + e.cost;
                q.emplace(dist[to], to);
            }
        }
    }
    return dist;
    // returns numeric_limits<T>::max() if there's no path
}