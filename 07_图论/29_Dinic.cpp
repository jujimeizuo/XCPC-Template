
struct Dinic {
    static const int N = 1e3 + 10, M = 2e5 + 10, INF = 0x3f3f3f;
    int n, m, s, t;
    int maxflow;
    int deep[N], cur[N];

    struct Edge {
        int v, next;
        int cap;
    }e[M << 1];
    int head[M << 1], cnt;

    void init() {
        memset(head, -1, sizeof head);
        cnt = maxflow = 0;
    }

    void add(int u, int v, int cap) {
        e[cnt].v = v;
        e[cnt].cap = cap;
        e[cnt].next = head[u];
        head[u] = cnt++;
        
        e[cnt].v = u;
        e[cnt].cap = 0;
        e[cnt].next = head[v];
        head[v] = cnt++;
    }

    bool bfs() {
        for(int i = 0;i <= t; i++) {
            deep[i] = -1, cur[i] = head[i];
        }
        queue<int> q;   
        q.push(s); deep[s] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
                for(int i = head[u]; ~i; i = e[i].next) {
                int v = e[i].v;
                if(deep[v] == -1 && e[i].cap) {
                    deep[v] = deep[u] + 1;
                    q.push(v);
                }
            }
        }
        if(deep[t] >= 0) return true;
        else return false;
    }

    int dfs(int u, int mx) {
        int a;
        if(u == t) return mx;
        for(int i = cur[u]; ~i; i = e[i].next) {
            cur[u] = i;
            int v = e[i].v;
            if(e[i].cap && deep[v] == deep[u] + 1 && (a = dfs(v, min(mx, e[i].cap)))) {
                e[i].cap -= a;
                e[i ^ 1].cap += a;
                return a;
            }
        }
        return 0;
    }

    void dinic() {
        while(bfs()) {
            while(1) {
                int res = dfs(s, INF);
                if(!res) break;
                maxflow += res;
            }
        }
    }
}mf;
