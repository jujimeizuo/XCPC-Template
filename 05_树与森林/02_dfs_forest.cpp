template <typename T>
class dfs_forest : public forest<T> {
public:
    using forest<T>::edges;
    using forest<T>::g;
    using forest<T>::n;
 
    std::vector<int> pv;
    std::vector<int> pe;
    std::vector<int> order;
    std::vector<int> pos;
    std::vector<int> end;
    std::vector<int> sz;
    std::vector<int> root;
    std::vector<int> depth;
    std::vector<T> dist;

    dfs_forest(int _n) : forest<T>(_n) {}

    void init() {
        pv = std::vector<int>(n, -1);
        pe = std::vector<int>(n, -1);
        order.clear();
        pos = std::vector<int>(n, -1);
        end = std::vector<int>(n, -1);
        sz = std::vector<int>(n, 0);
        root = std::vector<int>(n, -1);
        depth = std::vector<int>(n, -1);
        dist = std::vector<T>(n);
    }

    void clear() {
        pv.clear();
        pe.clear();
        order.clear();
        pos.clear();
        end.clear();
        sz.clear();
        root.clear();
        depth.clear();
        dist.clear();
    }

private:
    void do_dfs(int v) {
        pos[v] = (int) order.size();
        order.push_back(v);
        sz[v] = 1;
        for (int id : g[v]) {
            if (id == pe[v]) {
                continue;
            }
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            depth[to] = depth[v] + 1;
            dist[to] = dist[v] + e.cost;
            pv[to] = v;
            pe[to] = id;
            root[to] = (root[v] != -1 ? root[v] : to);
            do_dfs(to);
            sz[v] += sz[to];
        }
        end[v] = (int) order.size() - 1;
    }
 
    void do_dfs_from(int v) {
        depth[v] = 0;
        dist[v] = T{};
        root[v] = v;
        pv[v] = pe[v] = -1;
        do_dfs(v);
    }
 
public:
    void dfs(int v, bool clear_order = true) {
        if (pv.empty()) {
            init();
        } else {
            if (clear_order) {
                order.clear();
            }
        }
        do_dfs_from(v);
    }
 
    void dfs_all() {
        init();
        for (int v = 0; v < n; v++) {
            if (depth[v] == -1) {
                do_dfs_from(v);
            }
        }
        assert((int) order.size() == n);
    }
};