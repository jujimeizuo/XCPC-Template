ll get_Count(ll n) {
    ll ans = 1;
    for(int i = 2;i * i <= n; i++) {
        if(n % i == 0) {
            int a = 0;
            while(n % i == 0) {
                a++;
                n /= i;
            }
            ans *= (a + 1);
        }
    }
    if(n > 1)  ans *= 2;
    return ans;
}

ll get_Sum(ll n) {
    ll ans = 1;
    for(int i = 2;i * i <= n; i++) {
        if(n % i == 0) {
            ll a = 1;
            while(n % i == 0) {
                n /= i;
                a *= i;
            }
            ans = ans * (a * i - 1) / (i - 1);
        }
    }
    if(n > 1) ans *= (n + 1);
    return ans;
}
