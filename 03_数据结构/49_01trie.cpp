#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 * 32 + 10;

int t[N][2];
int num[N];
int idx;

void insert(ll x) {
    int rt = 0;
    for(int i = 32;i >= 0; i--) {
        int v = x >> i & 1;
        if(!t[rt][v]) {
            t[idx][0] = t[idx][1] = 0;
            num[idx] = 0;
            t[rt][v] = idx++;
        }
        rt = t[rt][v];
        num[rt]++;
    }
}

void modify(ll x, int val) {
    int rt = 0;
    for(int i = 32;i >= 0; i--) {
        int v = x >> i & 1;
        rt = t[rt][v];
        num[rt] += val;
    }
}

ll query(ll x) {
    ll ans = 0;
    int rt = 0;
    for(int i = 32;i >= 0; i--) {
        int v = x >> i & 1;
        if(t[rt][!v] && num[t[rt][!v]]) {
            ans += 1 << i;
            rt = t[rt][!v];
        }
        else rt = t[rt][v];
    }
    return ans;
}

// 不能有两个相同的异或，加一个num数组，表示访问次数

int main() {
    int _ = read();
    while(_--) {
        idx = 1; t[0][0] = t[0][1] = 0;
        int n = read();
        vector<ll> a(n + 1);
        for(int i = 1;i <= n; i++) insert(a[i] = read());
        ll ans = 0;
        for(int i = 1;i <= n; i++) {
            modify(a[i], -1);
            for(int j = i + 1;j <= n; j++) {
                modify(a[j], -1);
                ans = max(ans, query(a[i] + a[j]));
                modify(a[j], 1);
            }
            modify(a[i], 1);
        }
        cout << ans << endl;
    }
}