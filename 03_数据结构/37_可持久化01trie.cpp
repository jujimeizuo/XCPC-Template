#include <bits/stdc++.h>
using namespace std;

const int N = 2e7 + 10;

int t[N][2];
int cnt, root[N], sz[N][2];
int a[N];

void insert(int pre, int &now, int i, int x) {
    if(i < 0) return ;
    now = ++cnt;
    int d = x >> i & 1;
    t[now][d ^ 1] = t[pre][d ^ 1]; 
    sz[now][d ^ 1] = sz[pre][d ^ 1]; sz[now][d] = sz[pre][d] + 1;
    insert(t[pre][d], t[now][d], i - 1, x);
}

int query(int l, int r, int i, int x) {
    if(i < 0) return 0;
    int d = x >> i & 1;
    int tmp = sz[r][d ^ 1] - sz[l][d ^ 1];
    if(tmp > 0) return query(t[l][d ^ 1], t[r][d ^ 1], i - 1, x) + (1 << i);
    else return query(t[l][d], t[r][d], i - 1, x);
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n; i++) {
        int x;
        cin >> x;
        insert(root[i - 1], root[i], 30, x);
    }
    while(m--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << query(root[l - 1], root[r], 30, x) << endl;
    }
}