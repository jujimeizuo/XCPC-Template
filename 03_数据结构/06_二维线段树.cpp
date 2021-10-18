#define lc u << 1
#define rc u << 1 | 1
#define m (l + r) / 2

const int N = 1e3 + 10;

struct Tree_y {
    int mx, mn;

    Tree_y operator + (const Tree_y &rhs) {
        Tree_y ans;
        ans.mx = max(mx, rhs.mx);
        ans.mn = min(mn, rhs.mn);
        return ans;
    }
};

int leafx[N], leafy[N];

struct Tree_x {
    Tree_y ty[N << 2];

    void build(int u, int l, int r) {
        ty[u].mx = -INF; ty[u].mn = INF;
        if(l == r) {
            leafy[l] = u;
            return ;
        }
        build(lc, l, m);
        build(rc, m + 1, r);
    }

    Tree_y query(int u, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return (Tree_y) {-INF, INF};
        if(ql <= l && r <= qr) return ty[u];
        return query(lc, l, m, ql, qr) + query(rc, m + 1, r, ql, qr);
    }
}tx[N << 2];

int n;

void build(int u, int l, int r) {
    tx[u].build(1, 1, n);
    if(l == r) {
        leafx[l] = u;
        return ;
    }
    build(lc, l, m);
    build(rc, m + 1, r);
}

// (x,y)单点更新，首先更新叶子节点，然后向上合并父亲节点
void modify(int x, int y, int val) {
    int valx = leafx[x];
    int valy = leafy[y];
    tx[valx].ty[valy].mn = tx[valx].ty[valy].mx = val;
    for(int i = valx; i; i >>= 1) {
        for(int j = valy; j; j >>= 1) {
            if(i == valx && j == valy) continue ;
            if(j == valy) {
                // 如果当前更新的列就是需要更新的叶子节点，那么由当前行的两个儿子节点来更新
                tx[i].ty[j] = tx[i << 1].ty[j] + tx[i << 1 | 1].ty[j];
            }
            else {
                tx[i].ty[j] = tx[i].ty[j << 1] + tx[i].ty[j << 1 | 1];
            }
        }
    }
}

Tree_y query(int u, int l, int r, int ql, int qr, int qx, int qy) {
    if(qr < l || r < ql) return (Tree_y) {-INF, INF};
    if(ql <= l && r <= qr) return tx[u].query(1, 1, n, qx, qy);
    return query(lc, l, m, ql, qr, qx, qy) + query(rc, m + 1, r, ql, qr, qx, qy);
}
