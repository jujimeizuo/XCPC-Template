
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

struct Node {
    int l, r, val;
}hjt[N * 40];
int cnt, root[N];
int a[N];

inline void build(int &now, int l, int r) {
    now = ++cnt;
    if(l == r) {
        hjt[now].val = a[l];
        return ;
    }
    int m = (l + r) >> 1;
    build(hjt[now].l, l, m);
    build(hjt[now].r, m + 1, r);
}

inline void modify(int ver, int &now, int l, int r, int pos, int value) {
    hjt[now = ++cnt] = hjt[ver];
    if(l == r) {
        hjt[now].val = value;
        return ;
    }
    int m = (l + r) >> 1;
    if(pos <= m) modify(hjt[ver].l, hjt[now].l, l, m, pos, value);
    else modify(hjt[ver].r, hjt[now].r, m + 1, r, pos, value);
}

inline int query(int now, int l, int r, int pos) {
    if(l == r) return hjt[now].val;
    int m = (l + r) >> 1;
    if(pos <= m) return query(hjt[now].l, l, m, pos);
    else return query(hjt[now].r, m + 1, r, pos); 
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n; i++) cin >> a[i];
    build(root[0], 1, n);
    for(int i = 1;i <= m; i++) {
        int ver, opt;
        cin >> ver >> opt;
        if(opt == 1) {
            int pos, value;
            cin >> pos >> value;
            modify(root[ver], root[i], 1, n, pos, value);
        }
        else {
            int pos;
            cin >> pos;
            root[i] = root[ver];
            cout << query(root[i], 1, n, pos) << endl;
        }
    }
}