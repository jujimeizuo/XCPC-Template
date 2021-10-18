const int maxn = 2e5 + 10;

struct Edge {
    int v, next;
    ll w;
}e[maxn];
int head[maxn], cnt;

inline void add(int u, int v, ll w) ;

struct node {
    int now;
    ll d;
    bool operator < (const node &rhs) const {
        return d > rhs.d;
    }
};

ll dis[maxn];
bool vis[maxn];
priority_queue<node> q;

void dij(int s) {
    dis[s] = 0;
    q.push({s, 0});
    while(!q.empty()) {
        node p = q.top();
        q.pop();
        int u = p.now;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            if(dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                q.push({v, dis[v]});
            }
        }
    }
}