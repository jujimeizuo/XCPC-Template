struct HashTable {
    static const int MOD = 1e7 + 10;
    struct edge {
        int nxt;
        ll num, val;
    } e[MOD];
    int head[MOD], tot;
    void clear() { tot = 0; memset(head, 0, sizeof(head)); }
    void add(ll u, ll w) { e[++tot] = edge{head[u % MOD], u, w }, head[u % MOD] = tot; }
    void insert(ll u, ll w) {
        for(int i = head[u % MOD]; i; i = e[i].nxt) {
            if(e[i].num == u) { e[i].val += w; return ; }
        }
        add(u, w);
    }
    int find(ll u) {
        for (int i = head[u % MOD]; i; i = e[i].nxt)
            if (e[i].num == u) return e[i].val;
        return -1;
    }
} hs;
