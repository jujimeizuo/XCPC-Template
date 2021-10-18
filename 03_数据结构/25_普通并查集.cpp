const int N = 1e5 + 10;

int f[N], dep[N];

inline int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

inline void merge(int x, int y) {
    int u = find(x);
    int v = find(y);
    if(u == v) return ;
    else {
        if(dep[u] <= dep[v]) { f[u] = v; dep[v] = max(dep[v], dep[u] + 1); }
        else { f[v] = u; dep[u] = max(dep[u], dep[v] + 1); }
    }
}