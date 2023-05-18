// a和c不互质
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

template <typename T>
T ex_bsgs(T& a, T& b, T& c) {
    a %= c; b %= c;
    if (b == 1) return 0;
    T k = 0, tmp = 1, d;
    while (true) {
        d = __gcd(a, c);
        if (d == 1) {
            break ;
        }
        if (b % d) {
            return -1;
        }
        b /= d; c /= d;
        tmp = tmp * (a / d) % c;
        k++;
        if (tmp == b) {
            return k;
        }
    }
    std::unordered_map<T, T> mp;
    T m = std::ceil(sqrt((double) c));
    T x = 1, p = 1;
    for(T j = 0;j < m; j++, p = p * a % c) {
        mp[p * b % c] = j;
    }
    x = tmp % c;
    for(T i = 1 ;i <= m; i++) { // 枚举a^im
        x = x * p % c;
        if(mp[x]) {
            return k + i * m - mp[x];
        }
    }
    return -1;
}
