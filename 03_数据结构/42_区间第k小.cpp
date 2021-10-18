#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> v;
struct Node {
    int l, r;
    int val;
}hjt[N * 40];
int root[N], cnt;

int get_id(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin() + 1; }

void insert(int pre, int &now, int l, int r, int p) {
    hjt[++cnt] = hjt[pre];
    now = cnt;
    hjt[now].val++;
    if(l == r) return ;
    int m = (l + r) >> 1;
    if(p <= m) insert(hjt[pre].l, hjt[now].l, l, m, p);
    else insert(hjt[pre].r, hjt[now].r, m + 1, r, p);
}

int query(int L, int R, int l, int r, int k) {
    if(l == r) return l;
    int m = (l + r) >> 1;
    int tmp = hjt[hjt[R].l].val - hjt[hjt[L].l].val;
    if(k <= tmp) return query(hjt[L].l, hjt[R].l, l, m, k);
    else return query(hjt[L].r, hjt[R].r, m + 1, r, k - tmp); 
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1;i <= n; i++) { cin >> a[i]; v.push_back(a[i]); }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 1;i <= n; i++) {
        insert(root[i - 1], root[i], 1, n, get_id(a[i]));
    }

    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << v[query(root[l - 1], root[r], 1, n, k) - 1] << endl;
    }
}
