#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6 + 10;

unordered_map<int, ll> smu, sphi;
bool isPrime[N];
int prime[N], num;
ll mu[N], phi[N];

void makeMobiusAndEuler(int siz) {
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= siz; i++) {
        if (!isPrime[i]) prime[++num] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= num && i * prime[j] <= siz; j++) {
            isPrime[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else {
                phi[i * prime[j]] = phi[prime[j]] * phi[i];
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= siz; i++) mu[i] += mu[i - 1], phi[i] += phi[i - 1];
}

ll getSmu(int n) {
    if (n < N) return mu[n];
    if (smu[n]) return smu[n];
    ll res = 1;
    for (unsigned int l = 2, r = 0; l <= n; l = r + 1) {
        r = n / (n / l);
        res -= 1ll * (r - l + 1) * getSmu(n / l);
    }
    return smu[n] = res;
}

ll getSphi(int n) {
    if (n < N) return phi[n];
    if (sphi[n]) return sphi[n];
    ll res = 1ll * n * (n + 1) / 2;
    for (unsigned int l = 2, r = 0; l <= n; l = r + 1) {
        r = n / (n / l);
        res -= 1ll * (r - l + 1) * getSphi(n / l);
    }
    return sphi[n] = res;
}
