//三重循环，暴力遍历
#define INF 336860180
int n, m, d[405][405];
void Floyd() {
    memset(d, 20, sizeof d);
    for(int i = 1;i <= m; i++) {
        int u, v, h; cin >> u >> v >> h;
        d[u][v] = h;
    }
    for(int k = 1;k <= n; k++) {
        for(int i = 1;i <= n; i++) {
            for(int j = 1;j <= n; j++) {
                d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
            }
        }
    }
}