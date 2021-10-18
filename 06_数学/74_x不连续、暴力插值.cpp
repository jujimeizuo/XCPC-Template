
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = acos(-1);
const int N = 3e5 + 10;

ll mod;
ll X[N], Y[N];

ll quick_pow(ll a, ll b) ;

ll Lagrange(ll *x, ll *y, int n, int k) {
    ll ans = 0;
    for(int i = 0;i < n; i++) {
        ll s1 = 1, s2 = 1;
        for(int j = 0;j < n; j++) {
            if(i == j) continue;
            s1 = s1 * (k - x[j] + mod) % mod;
            s2 = s2 * (x[i] - x[j] + mod) % mod; 
        }
        ans = (ans + 1ll * y[i] * s1 % mod * quick_pow(s2, mod - 2) % mod) % mod;
    }
    return ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 0;i < n; i++) cin >> X[i] >> Y[i];
    cout << Lagrange(X, Y, n, k) << endl;
}
