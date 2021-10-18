// a和c不互质
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll EX_BSGS(ll a, ll b, ll c) {
    a %= c;
    b %= c;

    if(b == 1) return 0;

    ll k = 0, tmp = 1, d;
    while(true) {
        d = gcd(a, c);
        if(d == 1)
            break;
        if(b % d) // 无解
            return -1;
        b /= d; c /= d;
        tmp = tmp * (a / d) % c;
        k++;
        if(tmp == b)
            return k;
    }

    map<ll, ll> mp;
    mp.clear();

    ll m = ceil(sqrt((double)c)); // 向上取整
    ll x = 1, p = 1;
    for(ll j = 0;j < m; j++, p = p * a % c) {// 0 ~ m - 1
        mp[p * b % c] = j;
    }

    x = tmp % c;

    for(ll i = 1 ;i <= m; i++) { // 枚举a^im
        x = x * p % c;
        if(mp[x]) {
            return k + i * m - mp[x];
        }
    }
    return -1;
}

int main() {
    ll a, b, c;
    cin >> a >> b >> c;
    cout << EX_BSGS(a, b, c) << endl;
}
