#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;

#define endl "\n"
#define INF 0x3f3f3f3f
#define eb emplace_back
#define mem(a, b) memset(a , b , sizeof(a))

// const ll mod = 998244353;
 const ll mod = 1e9 + 7;
const double eps = 1e-6;
const double PI = acos(-1);
const double R = 0.57721566490153286060651209;

const int N = 3e6 + 10;

vector<int> g[N];

void solve() {
    int _; cin >> _;
    while(_--) {

    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
#ifdef FZT_ACM_LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
    signed test_index_for_debug = 1;
    char acm_local_for_debug = 0;
    do {
        if (acm_local_for_debug == '$') exit(0);
        if (test_index_for_debug > 20)
            throw runtime_error("Check the stdin!!!");
        auto start_clock_for_debug = clock();
        solve();
        auto end_clock_for_debug = clock();
        cout << "Test " << test_index_for_debug << " successful" << endl;
        cerr << "Test " << test_index_for_debug++ << " Run Time: "
             << double(end_clock_for_debug - start_clock_for_debug) / CLOCKS_PER_SEC << "s" << endl;
        cout << "--------------------------------------------------" << endl;
    } while (cin >> acm_local_for_debug && cin.putback(acm_local_for_debug));
#else
    solve();
#endif
    return 0;
}
