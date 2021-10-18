const int N = 1e5 + 10;
int d[N], vis[N];
vector<int> g[N];

int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> a(m + 1);
    for(int i = 1;i <= m; i++) {
        cin >> a[i].first >> a[i].second;
        d[a[i].first]++;
        d[a[i].second]++;
    }
    for(int i = 1;i <= m; i++) {
        int u = a[i].first, v = a[i].second;
        if(d[u] < d[v] || (d[u] == d[u] && u > v)) swap(u, v);
        g[u].push_back(v);    
    }
    int ans = 0;
    for(int u = 1;u <= n; u++) {
        for(auto v : g[u]) vis[v] = u;
        for(auto v : g[u]) {
            for(auto z : g[v]) {
                if(vis[z] == u) ans++;
            }
        }
    }
    cout << ans << endl;
    
}
