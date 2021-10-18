int v[1005], w[1005], s[1005];
int f[1005];

void mulbag() {
    int N, T;
    cin >> N >> T;
    for(int i = 1;i <= N; i++)
        cin >> v[i] >> w[i] >> s[i];
    for(int i = 1;i <= N; i++) {
        for(int j = T;j >= 0; j--) {
            for(int k = 1;k <= s[i]; k++) {
                if(j - k * v[i] >= 0)
                    f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);
            }
        }
    }
    cout << f[T] << endl;
}
