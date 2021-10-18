#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;

int n, m;
vector<int> vec[maxn];
int vis[maxn]; // 标记数组

void DFS(int u)
{
    vis[u] = 1;
    for(int i = 0;i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(vis[v] == 0)
            DFS(v);
    }
}

void solve() {
    cin >> n >> m;
    int u, v;
    for(int i = 1;i <= m; i++) {
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    int ans = 0;
    for(int i = 1;i <= n; i++) {
        if(vis[i] == 0) {
            DFS(i);
            ans++;
        }
    }
    cout << ans << endl;
}