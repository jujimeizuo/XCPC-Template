  
/*
差分约束是解决这样一类问题
给出n个形如x[j] − x[i] <= k的式子，求x[n] − x[1]的最大/最小值
最大值—>把所有式子整理为x[j] − x[i] <= k，从i向j连一条边权为k的边，跑最短路
最小值—>把所有式子整理为x[j] − x[i] >= k，从i向j连一条边权为k的边，跑最长路
注意初始化 有时候需要超级源点0
*/

bool spfa(int u) {//dfs跑差分约束最短路
    vis[u] = 1;
    for (int i = head[u], v; i; i = e[i].nxt)
        if (dis[u] + e[i].w < dis[v = e[i].to]) {
            if (vis[v]) return false;
            else {
                dis[v] = dis[u] + e[i].w;
                if (!spfa(v)) return false;
            }
        }
    vis[u] = 0;
    return true;
}