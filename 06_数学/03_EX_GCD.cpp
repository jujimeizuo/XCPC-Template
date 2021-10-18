typedef long long ll;

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    ll res, t;
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    res = ex_gcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - (a / b) * y;
    return res;
}

ll INV(ll a, ll mod) {
    ll x, y;
    ll d = ex_gcd(a, mod, x, y);
    return d ? (x % mod + mod) % mod : -1;
}
 
ll solve_ex_gcd(ll a, ll b, ll c, ll &x, ll &y) {
    ll d = ex_gcd(a, b, x, y);
    if(c % d)
    {
        x = -1;
        y = -1;
        return -1;
    }
    x *= (c / d);
    b = abs(b / d);
    x = (x % b + b) % b;
    y = (c - a * x) / (b * d);
    return 0;
}

int main() {
    ll x, y;
    cout << solve_ex_gcd(2, 3, 4, x, y) << endl; 
}
