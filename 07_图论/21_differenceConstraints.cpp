  
/*
差分约束是解决这样一类问题
给出n个形如x[j] − x[i] <= k的式子，求x[n] − x[1]的最大/最小值
最大值—>把所有式子整理为x[j] − x[i] <= k，从i向j连一条边权为k的边，跑最短路
最小值—>把所有式子整理为x[j] − x[i] >= k，从i向j连一条边权为k的边，跑最长路
注意初始化 有时候需要超级源点0
*/

//dfs跑差分约束最短路
template <typename T>
bool differenceConstraints(const graph<T>& g) {
    std::vector<bool> was(g.n);
    std::vector<T> dist(g.n, std::numeric_limits<T>::max());
    std::function<bool(int)> spfa = [&](int u) -> bool {
        was[u] = true;
        for (int id : g.g[u]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ to;
            if (dist[u] + e.cost < dist[to]) {
                if (was[to]) return false;
                dist[to] = dist[u] + e.cost;
                if (!spfa(to)) return false;
            }
        }
        was[u] = false;
        return true;
    };
    return spfa(0);
}