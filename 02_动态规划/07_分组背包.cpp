int v[2005], w[2005];
int f[2005];

void Divbag() {
    int n, V;
    cin >> n >> V;
    for(int i = 1;i <= n; i++) {
        int s;
        cin >> s;
        for(int j = 1;j <= s; j++) {
            cin >> v[j] >> w[j];
        }
        for(int j = V;j >= 0; j--) {
            for(int k = 1;k <= s; k++) {
                if(j >= v[k]) {
                    f[j] = max(f[j], f[j - v[k]] + w[k]);
                }
            }
        }
    }
    cout << f[V] << endl;
}

