class DSU {
private :
    std::vector<int> f, siz;
    
public :
    DSU(int n) : f(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1;i <= 2 * n; i++) f[i] = i;// **

    while(q--) {
        int flag, x, y;
        cin >> flag >> x >> y;
        if(flag) { // 敌人
            merge(x + n, y);
            merge(y + n, x);
        }
        else {
            merge(x, y); // 同伴
        }
    }    
    int ans = 0;
    for(int i = 1;i <= n; i++) {
        if(f[i] == i) ans ++;
    }
    cout << ans << endl;
}
