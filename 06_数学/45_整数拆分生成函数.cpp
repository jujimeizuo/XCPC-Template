
// O(n*sqrt(n))

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;
const ll mod = 1e9 + 7;
int f1[270], f2[270];

ll ans[N];

void init() {
    for (int i = 1; ; i++) {
        f1[i] = (3 * i * i - i) >> 1;
        if (f1[i] > 100000) break;
        f2[i] = (3 * i * i + i) >> 1;
        if (f2[i] > 100000) break;
    }
    ans[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        for (int j = 1; ; j++) {
            if (f1[j] <= i) ans[i] += j & 1 ? ans[i-f1[j]] : -ans[i-f1[j]];
            else break;
            if (f2[j] <= i) ans[i] += j & 1 ? ans[i-f2[j]] : -ans[i-f2[j]];
            else break;
        }
        ans[i] = (ans[i] % mod + mod) % mod;
    }
}
