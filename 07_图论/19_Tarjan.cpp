template <typename T>
class tarjan {
public:
    digraph<T> &g;
    int tim;
    std::vector<int> dfn;
    std::vector<int> low;
    std::vector<bool> vis;
    std::stack<int> s;
    std::set<int> cutVertexs;
    std::vector<std::array<int, 2>> cutBridges;
    std::vector<std::vector<int>> cycles;
    int root;
    tarjan(digraph<T> &_g) : g(_g) {
        dfn.resize(g.n);
        low.resize(g.n);
        vis.resize(g.n);
        tim = 1;
    }

    void dfs(int u) {
        s.push(u);
        dfn[u] = low[u] = tim++;
        vis[u] = true;
        int child = 0;
        for (int id : g.g[u]) {
            auto &e = g.edges[id];
            int to = e.to;
            if (!dfn[to]) {
                dfs(to);
                low[u] = std::min(low[u], low[to]);
                // if u is not root and low value of one of its child is more than dfn value of u
                // if u is root of DFS tree and has two or more children
                if (low[to] >= dfn[u]) {
                    child++;
                    if (u != root || child >= 2) {
                        cutVertexs.insert(u);
                    }
                }
                // if the lowest vertex reachable from subtree under v is below u is DFS tree, the u-b is a bridge
                if (low[to] > dfn[u]) {
                    cutBridges.push_back({std::min(u, to), std::max(u, to)});
                }
            } else if (vis[to]) {
                low[u] = std::min(low[u], dfn[to]);
            }
        }

        // find a strongly connected component
        if (dfn[u] == low[u]) {
            int from, cnt = 0;
            std::vector<int> cycle;
            do {
                from = s.top();
                cycle.push_back(from);
                vis[from] = false;
                s.pop();
                cnt++;
                // TODO ... num of connected component = cnt
            } while (from != u);
            cycles.push_back(cycle);
        }
    }

    void solve() {
        std::vector<std::vector<int>> cycles;
        for (int i = 0; i < g.n; i++) {
            if (!dfn[i]) {
                root = i;
                dfs(i);
            }
        }
    }
};