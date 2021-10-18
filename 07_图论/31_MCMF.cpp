const int maxn = 1005;      //点数

struct Edge {
    int from, to, cap, flow, cost;

    Edge(int u, int v, int c, int f, int cc)
            : from(u), to(v), cap(c), flow(f), cost(cc) {}
};

struct MCMF {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn];  //是否在队列中
    int d[maxn];    //bellmanford
    int p[maxn];    //上一条弧
    int a[maxn];    //可改进量
    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; ++i) G[i].clear();
        edges.clear();
    }

    void add(int from, int to, int cap, int cost) {
        edges.emplace_back(Edge(from, to, cap, 0, cost));
        edges.emplace_back(Edge(to, from, 0, 0, -cost));
        m = int(edges.size());
        G[from].emplace_back(m - 2);
        G[to].emplace_back(m - 1);
    }

    bool spfa(int s, int t, int &flow, int &cost) {
        for (int i = 1; i <= n; ++i) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        queue<int> q;
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
                    a[e.to] = min(a[u], e.cap - e.flow);
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
} mcmf;