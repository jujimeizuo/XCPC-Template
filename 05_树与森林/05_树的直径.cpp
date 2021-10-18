const int N = 1e5 + 10;

struct Edge {
    int v, w;
};
vector<Edge> g[N];
int dp[N][2];
int ans;

void dfs(int u, int fa) {
    for(auto e : g[u]) {
        int v = e.v;
        if(v == fa) continue;
        dfs(v, u);
        if(dp[v][0] + e.w > dp[u][0]) {
            dp[u][1] = dp[u][0];
            dp[u][0] = dp[v][0] + e.w;
        }
        else if(dp[v][0] + e.w > dp[u][1]) dp[u][1] = dp[v][0] + e.w;
    }
    ans = max(ans, dp[u][0] + dp[u][1]);
}