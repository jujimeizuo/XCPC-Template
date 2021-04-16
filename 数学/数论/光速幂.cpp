
ll v_pow(ll a, ll b) {
    ll ans = 1;
    ll base = 65536, k = 1;
    while(1) {
        if((b % (k * base)) / k == 0) break;
        ans = ans * quick_pow(a, (b % (k * base)) / k) % mod;
        a = quick_pow(a, base) % mod;
        k = k * base;
    }
    return ans;
}
