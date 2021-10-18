//Kruskal算法求最小生成树（稀疏图）

// 一个无向图，求最小生成树各边的和

struct Kruskal {
    static const int N = 1e6 + 10;
    int n, m, ans;
    struct Edge {
        int u, v, w;
        bool operator < (const Edge& rhs) const {
            return w < rhs.w;
        }
    }e[N << 1];
    int f[N];

    void init() {
        for(int i = 1;i <= n; i++) f[i] = i;
        m = 0;
    }

    void add(int u, int v, int w) {
        e[++m] = {u, v, w};
    }

    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }

    void kruskal() {
        int cnt = 0;
        sort(e + 1, e + m + 1);
        for(int i = 1;i <= m; i++) {
            int u = find(e[i].u);
            int v = find(e[i].v);
            if(u == v) continue;
            f[v] = u; ans += e[i].w;
            if(++cnt == n - 1) break;
        }
    }
}krl;