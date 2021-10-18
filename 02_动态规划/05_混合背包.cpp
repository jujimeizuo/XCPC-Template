struct Good {
    int v, w, kind;
};

int f[2005];
void mulbag2() {
    int n, V;
    cin >> n >> V;
    vector<Good> goods;
    for(int i = 1;i <= n; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        if(s < 0) {
            goods.push_back({v, w, -1});
        }
        else if(s == 0) {
            goods.push_back({v, w, 0});
        }
        else {
            for(int k = 1;k <= s; k *= 2) {
                s -= k;
                goods.push_back({v * k, w * k, -1});
            }
            if(s > 0) 
                goods.push_back({v * s, w * s, -1});
        }
    }
    for(auto good: goods) {
        if(good.kind == -1) {
            for(int j = V;j >= good.v; j--) {
                f[j] = max(f[j], f[j - good.v] + good.w);
            }
        }
        else {
            for(int j = good.v;j <= V; j++) {
                f[j] = max(f[j], f[j - good.v] + good.w);
            }
        }
    }
    cout << f[V] << endl;
}
