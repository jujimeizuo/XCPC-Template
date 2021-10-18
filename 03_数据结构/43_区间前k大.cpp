
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int a[N];
vector<int> v;
int cnt, root[N];

struct Node {
    int l, r;
    ll sum;
    int num;
    int val;
}hjt[N * 40];

int getid(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin() + 1; }

void insert(int pre, int &now, int l, int r, int p, int val) {
    now = ++cnt;
    hjt[now] = hjt[pre];
    hjt[now].num++; hjt[now].sum += val;
    if(l == r) {
        hjt[now].val = val;
        return ;
    }
    int m = (l + r) >> 1;
    if(p <= m) insert(hjt[pre].l, hjt[now].l, l, m, p, val);
    else insert(hjt[pre].r, hjt[now].r, m + 1, r, p, val);
}

ll query(int L, int R, int l, int r, int k) {
    if(l == r) return hjt[R].val * k;
    int m = (l + r) >> 1;
    int tmp = hjt[hjt[R].r] .num - hjt[hjt[L].r].num;
    if(k <= tmp) return query(hjt[L].r, hjt[R].r, m + 1, r, k);
    else return hjt[hjt[R].r].sum - hjt[hjt[L].r].sum + query(hjt[L].l, hjt[R].l, l, m, k - tmp);
}

void init(int n) {
    v.clear();
    cnt = 0;
    for(int i = 1;i <= n; i++) {
        scanf("%d",&a[i]);
        v.push_back(a[i]); root[i] = 0;
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

int main() {
    int _;
    scanf("%d",&_);
    while(_--) {
        int n;
        scanf("%d",&n);
        init(n);
        for(int i = 1;i <= n; i++) {
            insert(root[i - 1], root[i], 1, n, getid(a[i]), a[i]);
        }
        int q;
        scanf("%d",&q);
        while(q--) {
            int l, r, k;
            scanf("%d%d%d",&l,&r,&k);
            int t = r - l + 1;
            ll ans = query(root[l - 1], root[r], 1, n, k);
            printf("%lld\n",1ll * t * (t + 1) * (2 * t + 1) / 6 + ans);
        }
    }
}
