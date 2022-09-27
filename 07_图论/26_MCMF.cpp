struct MCMF {
    struct Edge {
    int from, to, cap, flow, cost;
    Edge(int u, int v, int c, int f, int cc)
        : from(u), to(v), cap(c), flow(f), cost(cc) {}
    };
    static constexpr int INF = 1e9;
    int n, m;
    
    std::vector<Edge> edges;
    std::vector<std::vector<int>> G;
    std::vector<int> inq;
    std::vector<int> d;
    std::vector<int> p;
    std::vector<int> a;

    
    MCMF(int n) : n(n), G(n), inq(n), d(n), p(n), a(n) {}

    void add(int from, int to, int cap, int cost) {
        edges.emplace_back(Edge(from, to, cap, 0, cost));
        edges.emplace_back(Edge(to, from, 0, 0, -cost));
        m = int(edges.size());
        G[from].emplace_back(m - 2);
        G[to].emplace_back(m - 1);
    }

    bool spfa(int s, int t, int &flow, int &cost) {
        for (int i = 1; i < n; ++i) d[i] = INF;
        inq.assign(n, 0);
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        std::queue<int> q;
        a[s] = INF;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i = 0; i < int(G[u].size()); ++i) {
                Edge &e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = std::min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if (d[t] == INF) return false;
        flow += a[t];
        cost += d[t] * a[t];
        for (int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
        }
        return true;
    }

    int MincostMaxflow(int s, int t, int &cost) {
        int flow = 0;
        cost = 0;
        while (spfa(s, t, flow, cost));
        return flow;
    }
};