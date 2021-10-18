int v[1005], w[1005];
int f[1005];

void fsbag() {
    int n, V;
    cin >> n >> V;
    for(int i = 1;i <= n; i++) {
        cin >> v[i] >> w[i];
    }
    
    for(int i = 1;i <= n; i++) {
        for(int j = V;j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    
    cout << f[V] << endl;
}
