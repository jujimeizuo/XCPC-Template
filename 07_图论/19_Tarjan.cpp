
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

struct Edge{
    int u, v, next;
}e[N * 2];

int head[N], cnt;

int dfn[N], low[N]; // 第一次访问到的节点的编号和最早访问的节点的编号（时间戳）
bool vis[N]; // 标记节点是否访问过并且还在栈中
int Time = 1;
stack<int> s;

void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

void DFS(int u) {
    s.push(u);
    dfn[u] = low[u] = Time++;
    vis[u] = 1;

    for(int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if(!dfn[v]) {
            DFS(v);
            low[u] = min(low[u], low[v]); // 更新时间戳
        }
        else if(vis[v]) {
            low[u] = min(low[u], low[v]); // 更新时间戳
        }

    }

    if(dfn[u] == low[u]) { // 找到了一个强连通分量
        int x;
        do {
            x = s.top();
            cout << x << " ";
            vis[x] = 0;
            s.pop();
        }while(x != u);
        cout << endl;
    }
}

void Tarjan() {
    int n, m;
    cin >> n >> m;

    for(int i = 1;i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    
    for(int i = 1;i <= n; i++) {
        if(!dfn[i])
            DFS(i);
    }
}

