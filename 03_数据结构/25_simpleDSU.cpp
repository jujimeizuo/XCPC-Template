class DSU {
private :
    std::vector<int> f, siz;
    std::vector<int> dep;
public :
    DSU(int n) : f(n), dep(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if (dep[x] > dep[y]) std::swap(x, y);
        siz[y] += siz[x];
        f[x] = y;
        dep[y] = std::max(dep[y], dep[x] + 1);
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};