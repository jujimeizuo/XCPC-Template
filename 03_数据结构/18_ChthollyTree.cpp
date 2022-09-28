// 要先Split右端点(r+1)，在Split左端点(l)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
    int l, r;
    mutable ll v;
    node (int L, int R = -1, ll V = 0) : l(L), r(R), v(V) {}
    bool operator < (const node &rhs) const {
        return l < rhs.l;
    }
};

set<node> s;

auto Split(int pos) {
    auto it = s.lower_bound(node(pos));
    if(it != s.end() && it -> l == pos) return it;
    --it;
    int L = it -> l, R  = it -> r;
    ll V = it -> v;
    s.erase(it);
    s.insert(node(L, pos - 1, V));
    return s.insert(node(pos, R, V)).first;
}

void assign_val(int l, int r, ll val) { // 推平操作
    auto itr = Split(r + 1);
    auto itl = Split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, val));
}

void add(int l, int r, ll val) { // 区间加
    auto itr = Split(r + 1);
    auto itl = Split(l);
    for( ;itl != itr; ++itl) {
        itl -> v += val;
    }
}

ll kth(int l, int r, int k) { // 区间第k小
    vector<pair<ll, int> > v;
    auto itr = Split(r + 1);
    auto itl = Split(l);
    for( ;itl != itr; ++itl) {
        v.push_back(pair<ll, int>{itl -> v, itl -> r - itl -> l + 1});
    }
    sort(v.begin(), v.end());
    for(auto it = v.begin();it != v.end(); ++it) {
        k -= it -> second;
        if(k <= 0) return it -> first;
    }
}

ll quick_pow(ll a, ll b, ll p) ;

ll qpow(int l, int r, int ex, int p) {
    auto itr = Split(r + 1);
    auto itl = Split(l);
    ll ans = 0;
    for( ;itl != itr; ++itl)
        ans = (ans + ll(itl -> r - itl -> l + 1) * quick_pow(itl -> v, ll(ex), ll(p)) % ll(p)) % ll(p);
    return ans % ll(p);
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i){
        ll x;
        cin >> x;
        s.insert(node(i,i,x));
    }
    s.insert(node(n + 1, n + 1, 0));
    while(m--) {
        int opt, l, r, x;
        cin >> opt >> l >> r >> x;
        if(opt == 1) add(l, r, x);
        else if(opt == 2) assign_val(l, r, x);
        else if(opt == 3) cout << kth(l, r, x)  << endl;
        else {
            int y;
            cin >> y;
            cout << qpow(l, r, x, y) << endl;
        }
    }
}