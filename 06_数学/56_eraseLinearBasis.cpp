// 离线删除操作，维护线性基中每个元素的最晚删除时间。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxl = 60;

struct LinearBasis {
    ll a[maxl + 10], tim[maxl + 10]; 
    int n, size; // 每个相同异或值有2^{n-size}个
    vector<ll> v;

    LinearBasis() {
        memset(a, 0, sizeof(a));
        size = n = 0;
        v.clear();
    }

    void insert(ll x, ll t) {
        n++;
        for(int i = maxl;i >= 0; i--) {
            if(!(x >> i & 1)) continue ;
            if(a[i]) {
                if(t > tim[i]) swap(t, tim[i]), swap(x, a[i]);
                x ^= a[i];
            }
            else {
                ++size;
                a[i] = x; tim[i] = t;
                return ;
            }
        }
    }

    void erase(ll t) {
        for(int i = maxl;i >= 0; i--) {
            if(tim[i] == t) {
                a[i] = tim[i] = 0; --size;
                return ;
            }
        }
    }
};

int main() {
    LinearBasis lb;
    int n, m; cin >> n >> m;
    vector<ll> opt(n + 10), a(n + 10), del(n + 10), pre(n + 10);
    for(int i = 1;i <= m; i++) {
        cin >> opt[i] >> a[i];
        if(opt[i] == 1) pre[a[i]] = i, del[i] = m + 1;
        else del[pre[a[i]]] = i;
    }
    ll ans = 0;
    for(int i = 1;i <= m; i++) {
        if(opt[i] == 1) lb.insert(a[i], del[i]);
        else lb.erase(i);
        ans ^= 1ll << (lb.n - lb.size);
    }
    cout << ans << endl;
}