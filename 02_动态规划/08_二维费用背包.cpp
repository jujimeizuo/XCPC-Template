int f[2005][2005];

void TwoCostbag() {
    int n, M, V;
    cin >> n >> V >> M;
    for(int i = 1;i <= n; i++) {
        int v, m, w;
        cin >> v >> m >> w;
        for(int j = V;j >= v; j--) {
            for(int k = M;k >= m; k--) {
                f[j][k] = max(f[j][k], f[j - v][k - m] + w);
            }
        }
    }
    cout << f[V][M] << endl;
}

