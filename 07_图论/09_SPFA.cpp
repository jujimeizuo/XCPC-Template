#define INF 0x3f
#define maxn 5000005
int n, m, s;

struct Edge {
    int v, w, next;
}e[maxn];
int head[maxn], cnt, dis[maxn];
bool vis[maxn]; 

inline void add(int u,int v,int w) ;

queue<int> q;

void SPFA() {
    for(int i = 1;i <= n; i++) {
        dis[i] = INF;
        vis[i] = false;
    }
    q.push(s); dis[s] = 0; vis[s] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            if(dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
}