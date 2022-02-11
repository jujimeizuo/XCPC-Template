class Tarjan {
public :
    long long ans;
    const int n;
    int tim;
    vector<vector<int>> edge;
    vector<int> dfn, low;
    vector<bool> vis;
    stack<int> s;
    Tarjan(int n) : n(n), edge(n), dfn(n), low(n), vis(n), tim(1), ans(0) {}
    
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    void dfs(int u) {
        s.push(u);
        dfn[u] = low[u] = tim++;
        vis[u] = true;
        for(int v : edge[u]) {
            if(!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if(vis[v]) {
                low[u] = min(low[u], low[v]);
            }
        }
        // 找到一个联通分量
        if(dfn[u] == low[u]) {
            int from, cnt = 0;
            do {
                from = s.top();
                vis[from] = false;
                s.pop();
                cnt++;
                // TODO ... num = cnt
            }while(from != u);
        }
    }
    // for(int i = 1;i <= n; i++) if(!dfn[i]) dfs(i);
};
