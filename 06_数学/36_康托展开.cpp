#include  <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;

ll fac[N];
int a[N]; // 排列，康托展开求解
int n;
ll x; // 逆康托展开求解

void Get_F() {
    fac[0] = 1;
    for(int i = 1;i < N; i++)
        fac[i] = fac[i - 1] * i % mod;
}

ll CanTor() {
    ll ans = 0;
    for(int i = 1;i <= n; i++) {
        ll smaller = 0;
        for(int j = i + 1;j <= n; j++) {
            if(a[j] < a[i])
                smaller++;
        }
        ans = (ans + fac[n - i] * smaller % mod) % mod;
    }
    return ans + 1;
}

void DeCantor() {
    vector<int> v; // 存放当前可选数
    vector<int> a; // 所求的排列组合序
    for(int i = 1;i <= n; i++) {
        v.push_back(i);
    }
    for(int i = n;i >= 1; i--) {
        int r = x % fac[i - 1];
        int t = x / fac[i - 1];
        x = r;
        sort(v.begin(), v.end());
        a.push_back(v[t]);
        v.erase(v.begin() + t);
    }
    for(int i = 0;i < a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}

// 线段树优化

const int N = 1000010;

ll fac[N];
int a[N]; // 排列，康托展开求解
int n;

struct SegmentTree {
    int ls, rs;
    int sum;
}t[N << 2];

int cnt, root;

void push_up(int u) {
    t[u].sum = (t[lc].sum + t[rc].sum) % mod;
}

void build(int &u, int l, int r) {
    if(!u) u = ++cnt;
    if(l == r) {
        t[u].sum = 1;
        return ;
    }
    build(lc, l, m);
    build(rc, m + 1, r);
    push_up(u);
}

void update(int &u, int l, int r, int k) {
    if(!u) u = ++cnt;
    if(l == r) {
        t[u].sum = 0;
        return ;
    }
    if(k <= m) update(lc, l, m, k);
    else update(rc, m + 1, r, k);
    push_up(u);
}

ll query(int u, int l, int r, int ql, int qr) {
    if(ql > qr) return 0;
    if(ql == l && qr == r) {
        return t[u].sum;
    }
    if(qr <= m) return query(lc, l, m, ql, qr) % mod;
    else if(ql > m) return query(rc, m + 1, r, ql, qr) % mod;
    else return (query(lc, l, m, ql, m) + query(rc, m + 1, r, m + 1, qr)) % mod;
}

void Get_F() {
    fac[0] = 1;
    for(int i = 1;i < N; i++)
        fac[i] = fac[i - 1] * i % mod;
}

void solve()
{
    Get_F();
    cin >> n;
    build(root, 1, n);
    ll ans = 0;
    for(int i = 1;i <= n; i++) {
        cin >> a[i];
        update(root, 1, n, a[i]);
        ans = (ans + query(root, 1, n, 1, a[i] - 1) * fac[n - i]) % mod;
    }
    cout << (ans + 1) % mod << endl;
}