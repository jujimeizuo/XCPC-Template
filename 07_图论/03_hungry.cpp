#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 10;
struct Edge {
    int v, next;
}e[maxn << 1];
int head[maxn << 1], cnt;
bool vis[maxn << 1];
int match[maxn << 1];

inline void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

bool hungry(int u) {
    for(int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(!vis[v]) {
            vis[v] = true;
            if(match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve() {
    int k, m, n;
    while(scanf("%d",&k) && k) {
        mem(match, -1);
        cnt = 0;
        mem(head, -1);
        scanf("%d%d",&m,&n);
        for(int i = 1;i <= k; i++) {
            int u, v;
            scanf("%d%d",&u,&v);
            add(u, v);
        }
        int ans = 0;
        for(int i = 1;i <= m; i++) {
            mem(vis, false);
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
}