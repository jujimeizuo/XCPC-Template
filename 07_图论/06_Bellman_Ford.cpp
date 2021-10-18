struct Edge {
    int u, v, w;
}e[1005];
 
int dis[1005], n, m, s;
bool flag; // 判断负环
 
void Init() {
    cin >> n >> m >> s;
    for(int i = 1;i <= n; i++) dis[i] = INF;
    dis[s] = 0;
    for(int i = 1;i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        if(e[i].u == s)
            dis[e[i].v] = e[i].w;
    }
}
 
void Bellman_Ford() {
    for(int i = 1;i < n; i++) {
        for(int j = 1;j <= m; i++) {
            if(dis[e[j].v] > dis[e[j].u] + e[j].w)
                dis[e[j].v] = dis[e[j].u] + e[j].w;
        }
    }
    flag = true;
    for(int i = 1;i <= m; i++) {
        if(dis[e[i].v] > dis[e[i].u] + e[i].w) {
            flag = false;
            break;
        }
    }
}