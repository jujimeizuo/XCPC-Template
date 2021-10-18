int v[1005], w[1005];
int f[1005];

void cptbag() {
    int N, T;
    cin >> N >> T;
    for(int i = 1;i <= N; i++)
        cin >> v[i] >> w[i];
    for(int i = 1;i <= N; i++) {
        for(int j = 0;j <= T; j++) {
            if(j - v[i] >= 0)
                f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[T] << endl;
}
