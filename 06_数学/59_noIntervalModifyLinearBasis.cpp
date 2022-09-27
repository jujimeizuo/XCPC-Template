// 扫描r，维护线性基中每个元素的最大左端点l。与删除操作类似。
// 这个可以强制在线，把每个r的线性基存下来即可。
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
struct node {
    int l, r, id;
    bool operator < (const node &p) const {
        return r < p.r;
    }
}q[N];

const int maxl = 60;

struct LinearBasis {
    ll a[maxl + 10], pos[maxl + 10];
    int n, size; // 每个相同异或值有2^{n-size}个
    vector<ll> v;

    LinearBasis() {
        memset(a, 0, sizeof(a));
        size = n = 0;
        v.clear();
    }

    void insert(ll t, ll id) {
        n++;
        for(int i = maxl;i >= 0; i--) {
            if(!(t >> i & 1)) continue ;
            if(a[i]) {
                if(id > pos[i]) swap(id, pos[i]), swap(t, a[i]);
                t ^= a[i];
            }
            else {
                a[i] = t;
                pos[i] = id;
                return ;
            }
        }
    }

    int askmax(ll x) {
        ll ans = 0;
        for(int i = maxl;i >= 0; i--) {
//            if(pos[i] >= x && !(ans >> i & 1)) ans ^= a[i];
            if(pos[i] >= x) ans = max(ans, ans ^ a[i]);
        }
        return ans;
    }
};

// 给你n个数，每次查询 [公式] 这个区间，问着个区间的最大异或值。

void solve() {
    LinearBasis lb;
    int n; cin >> n;
    VI a(n + 1);
    for(int i = 1;i <= n; i++) cin >> a[i];
    int m; cin >> m;
    VI ans(m + 1);
    for(int i = 1;i <= m; i++) cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + m + 1);
    for(int i = 1, j = 1;i <= n; i++) {
        lb.insert(a[i], i);
        for(; j <= m && q[j].r <= i; j++) ans[q[j].id] = lb.askmax(q[j].l);
    }
    for(int i = 1;i <= m; i++) cout << ans[i] << endl;
}
