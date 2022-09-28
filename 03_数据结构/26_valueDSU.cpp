class DSU {
private :
    std::vector<int> f, siz, val;

public :
    DSU(int n) : f(n), val(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }

    int find(int x) {
        if (x != f[x]) {
            int fa = f[x];
            f[x] = find(f[x]);
            val[x] += val[fa];
        }
        return f[x];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y, int v) {
        int nx = find(x);
        int ny = find(y);
        if(nx == ny) return false;
        siz[nx] += siz[ny];
        f[ny] = nx;
        val[ny] = val[x] + v - val[y];
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};