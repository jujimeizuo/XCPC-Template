// 当[l,r]^x时，很不幸异或出来的结果不一定连续，而是分成多个连续区间，所以需要用线段树来构造一个区间异或x之后还是连续区间

// [0, 7]可以分成[0, 3]和[4, 7]，这样区间异或x还是连续区间

// 主要操作：

/*
把低pos位全为0
int ql = (l ^ val) & (((1 << 30) - 1) ^ (1 << pos) - 1);
int qr = ql + (1 << pos) - 1;
把低pos位全为1

高pos不管
*/

vector<pii> g[N], len;
int l[N], r[N];

void modify(int pos, int l, int r, int L, int R, int val) {
    if(L <= l && r <= R) {
        // 把低pos设置为0
        int ql = (l ^ val) & (((1 << 30) - 1) ^ (1 << pos) - 1);
        int qr = ql + (1 << pos) - 1;
        len.push_back(pii{ql, qr});
        return ;
    }
    int mid = (l + r) / 2;
    if(L <= mid) modify(pos - 1, l, mid, L, R, val);
    if(R  > mid) modify(pos - 1, mid + 1, r, L, R, val);
}

void dfs(int u, int fa, int w) {
    modify(30, 0, (1 << 30) - 1, l[u], r[u], w);
    for(auto e : g[u]) {
        if(e.fi == fa) continue ;
        dfs(e.fi, u, e.se ^ w);
    }
}
