// 树的最长路径

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int f[N][2];
int down[N], up[N];
int ans;

vector<int> g[N];

void dfs1(int u, int fa) {
    for(auto v : g[u]) {
        if(v == fa) continue ;
        dfs1(v, u);
        if(f[v][0] + 1 > f[u][0]) {
            f[u][1] = f[u][0];
            f[u][0] = f[v][0] + 1;
            down[u] = v;
        }
        else if(f[v][0] + 1 > f[u][1]) f[u][1] = f[v][0] + 1;
    }
    ans = max(ans, f[u][0] + f[u][1]);
}

void dfs2(int u, int fa) {
    for(auto v : g[u]) {
        if(v == fa) continue ;
        up[v] = up[u] + 1;
        if(down[u] == v) up[v] = max(up[v], f[u][1] + 1);
        else up[v] = max(up[v], f[u][0] + 1);
        dfs2(v, u);
    }
}

int main() {
    int n; cin >> n;
    for(int i = 1;i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    for(int i = 0;i < n; i++) {
        int d[3] = {f[i][1], f[i][0], up[i]};
        sort(d, d + 3);
        if(d[2] + d[1] == ans) cout << i << endl;
    }
}