// 权值线段树，相当于一个桶，每个节点用来表示一个区间的数***出现的次数***。

#include <bits/stdc++.h>

using namespace std;

#define lc u << 1
#define rc u << 1 | 1
#define m (l + r) / 2
#define mid (t[u].l + t[u].r) / 2

const int N = 1e5 + 10;

int t[N << 2];

int a[N];

void push_up(int u) {
    t[u] = t[lc] + t[rc];
}

void build(int u, int l, int r) {
    if(l == r) {
        t[u] = a[l]; // a[l]表示数为l的个数
        return ;
    }
    build(lc, l, m);
    build(rc, m + 1, r);
    push_up(u);
}

void update(int u, int l, int r, int k, int cnt) { // k这个数的个数增加cnt
    if(l == r) {
        t[u] += cnt;
        return ;
    }
    if(k <= m)
        update(lc, l, m, k, cnt);
    else
        update(rc, m + 1, r, k, cnt);
    push_up(u); 
}

int query(int u, int l, int r, int k) { // 查询k这个数的个数
    if(l == r) {
        return t[u];
    }
    if(k <= m)
        return query(lc, l, m, k);
    else 
        return query(rc, m + 1, r, k);
}

int k_max_th(int u, int l, int r, int k) { // 查询第k大的值
    if(l == r) {
        return l;
    }
    if(t[lc] >= k) return k_max_th(lc, l, m, k);
    else return k_max_th(rc, m + 1, r, k - t[lc]);
}
