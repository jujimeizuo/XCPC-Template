// 二维平面里最近点对距离
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
struct node {
    ll x[2];
}a[N], b[N];

int now, n;
ll ans;
map<pair<ll, ll>, int> mp;

bool cmp(node a, node b) { return a.x[now] < b.x[now]; }

ll sqr(int x) { return (ll)x * x; }
ll dis(node a, node b) { return sqr(a.x[0] - b.x[0]) + sqr(a.x[1] - b.x[1]); }

void build(int l, int r, int d) {
    if(l >= r) return ;
    int m = (l + r) >> 1;
    now = d;
    nth_element(a + l, a + m, a + r, cmp);
    build(l, m, d ^ 1);
    build(m + 1, r, d ^ 1);
}

void query(int l, int r, int d, node p) {
    if(l >= r) return ;
    int m = (l + r) >> 1;
    int ql = l, qr = m;
    ll res = dis(a[m], p);
    if(ans == 0 || res && ans > res) ans = res;
    if(p.x[d] > a[m].x[d]) ql = m + 1, qr = r;
    query(ql, qr, d ^ 1, p);
    if(ans > sqr(a[m].x[d] - p.x[d]))
        query(l + m - ql + 1, m + r - qr, d ^ 1, p);
}

void solve() {
    scanf("%d",&n);
    ll sum = 5e18;
    for(int i = 0;i < n; i++) {
        scanf("%lld %lld",&a[i].x[0],&a[i].x[1]);
        if(mp[{a[i].x[0], a[i].x[1]}]) sum = 0;
        else mp[{a[i].x[0], a[i].x[1]}]++;
        b[i] = a[i];
    }
    build(0, n, 0);
    for(int i = 0;i < n; i++) {
        ans = 0;
        query(0, n, 0, b[i]);
        sum = min(ans, sum);
    }
    printf("%.4lf\n",sqrt(1.0 * sum));
}

