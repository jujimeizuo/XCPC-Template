struct ISAP {
    const static int N = ...;//node size
    struct Edge {
        int from, to, cap, flow;
        bool operator < (const Edge &rhs) const {
            return from < rhs.from || (from == rhs.from && to < rhs.to);
        }
    };
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> g[N];
    bool vis[N];
    int dep[N], cur[N], p[N], num[N];

    void addEdge(int from, int to, int cap) {
        edges.push_back(Edge{from, to, cap, 0});
        edges.push_back(Edge{to, from, 0, 0});
        m = edges.size();
        g[from].push_back(m - 2);
        g[to].push_back(m - 1);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q; q.push(t); vis[t] = 1, dep[t] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &v: g[u]) {
                Edge &e = edges[v ^ 1];
                if (!vis[e.from] && e.cap > e.flow) {
                    dep[e.from] = dep[u] + (vis[e.from] = 1);
                    q.push(e.from);
                }
            }
        }
        return vis[s];
    }

    void init(int siz) {
        n = siz;
        for (int i = 0; i < siz; i++) g[i].clear();
        edges.clear();
    }

    int augment() {
        int u = t, a = INF;
        while (u != s) {
            Edge &e = edges[p[u]];
            a = min(a, e.cap - e.flow);
            u = edges[p[u]].from;
        }
        u = t;
        while (u != s) {
            edges[p[u]].flow += a;
            edges[p[u] ^ 1].flow -= a;
            u = edges[p[u]].from;
        }
        return a;
    }

    int maxFlow(int S, int T) {
        s = S, t = T;
        int flow = 0; bfs();
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++) num[dep[i]]++;
        int u = S;
        memset(cur, 0, sizeof(cur));
        while (dep[S] < n) {
            if (u == T) {
                flow += augment();
                u = S;
            }
            int ok = 0;
            for (int i = cur[u]; i < g[u].size(); i++) {
                Edge &e = edges[g[u][i]];
                if (e.cap > e.flow && dep[u] == dep[e.to] + 1) {
                    ok = 1;
                    p[e.to] = g[u][i];
                    cur[u] = i;
                    u = e.to;
                    break;
                }
            }
            if (!ok) {
                int mn = n - 1;
                for (int i = 0; i < g[u].size(); i++) {
                    Edge &e = edges[g[u][i]];
                    if (e.cap > e.flow) mn = min(mn, dep[e.to]);
                }
                if (--num[dep[u]] == 0) break;
                num[dep[u] = mn + 1]++;
                cur[u] = 0;
                if (u != S) u = edges[p[u]].from;
            }
        }
        return flow;
    }

} flow;