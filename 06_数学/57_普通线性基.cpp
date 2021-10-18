// 每个异或值都相同的个数都为2^n-r,所以不同的异或值有2^r个. 
#include <bits/stdc++.h>
using namespace  std;

typedef long long ll;
const int maxl = 60;
ll quick_pow(ll a, ll b) ;
struct LinearBasis {
    ll a[maxl + 10]; 
    int n, size; // 每个相同异或值有2^{n-size}个
    vector<ll> v;

    LinearBasis() {
        memset(a, 0, sizeof(a));
        size = n = 0;
        v.clear();
    }

    void insert(ll t) {
        n++;
        for (int i = maxl; i >= 0; --i) {
            if (!(t >> i & 1)) continue;
            if (a[i]) t ^= a[i];
            else {
                ++size;
                // Rebuild 
                for (int j = i - 1; j >= 0; j--) if (t >> j & 1) t ^= a[j];
                for (int j = i + 1; j <= maxl; ++j) if (a[j] >> i & 1) a[j] ^= t;
                //
                a[i] = t;
                return;
            }
        }
    }

    // 与Rebuild配套使用
    void basis() {
        for (int i = 0; i <= maxl; ++i) if (a[i]) v.push_back(i);
    }

    // 查询能否xor出x这个数
    bool find(ll x) {
        for(int i = maxl;i >= 0; i--) {
            if(x >> i & 1) {
                if(!a[i]) return 0;
                x ^= a[i];
            }
        }
        return 1;
    }

    // 查询异或最大值
    ll askmax() {
        ll ans = 0;
        for(int i = maxl;i >= 0; i--) ans = max(ans, ans ^ a[i]);
        return ans;
    }

    // 查询异或最小值
    ll askmin() {
        for(int i = 0;i <= maxl; i++) if(a[i]) return a[i];
        return 0;
    }

    // 查询异或第k大
    ll askmaxk(ll x) {
        
    }

    // 查询异或第k小
    ll askmink(ll x) {
        if(v.size() != n) x--;
        if(!x) return 0;
        if(x >= (1ll << v.size())) return -1;
        ll ans = 0;
        for(int i = 0;i < v.size(); i++) {
            if(x >> i & 1) ans ^= a[v[i]];
        }
        return ans;
    }

    ll rank(ll x) {
        ll ret = 0;
        for (int i = 0; i < v.size(); ++i) if (x >> v[i] & 1) ret += 1LL << i;
        return ret;
    }
};


void solve() {
    int n, x, q;
    scanf("%d", &n);
    LinearBasis lb;
    for (int i = 0; i < n; ++i) scanf("%d", &x), lb.insert(x);
    lb.basis();
    scanf("%d", &q);
    ll num = quick_pow(2, n - lb.size);
    printf("%lld\n", (lb.rank(q) * num + 1));
}