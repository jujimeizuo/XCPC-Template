
int f[2005];
struct Good{
     int v, w;
};

void mulbag2() {
    int N, T;
    cin >> N >> T;
    vector<Good> goods;
    for(int i = 1;i <= N; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        for(int k = 1;k <= s; k *= 2) {
            s -= k;
            goods.push_back({v * k, w * k});
        }
        if(s > 0)
            goods.push_back({s * v, s * w});
    }
    for(auto good : goods) {
        for(int j = T;j >= good.v; j--) {
            f[j] = max(f[j], f[j - good.v] + good.w);
        }
    }
    cout << f[T] << endl;
}
