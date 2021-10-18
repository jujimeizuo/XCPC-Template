typedef long long ll;

ll a[10005]; // n个数
ll s[10005]; // 前缀积
ll invs[10005]; // 前缀积的逆元
ll inv[10005]; // a[i]的逆元

ll qucik_pow(ll a, ll b, ll mod) ;

void Line_INV() {
    s[0] = 1;
    ll p;
    for(int i = 1;i <= n; i++)
        cin >> a[i]; // 任意n个数
    cin >> p;
    for (int i = 1; i <= n; ++i) 
        s[i] = s[i - 1] * a[i] % p;
    sv[n] = quick_pow(s[n], p - 2);
    for (int i = n; i >= 1; --i) 
        sv[i - 1] = sv[i] * a[i] % p;
    for (int i = 1; i <= n; ++i) 
        inv[i] = sv[i] * s[i - 1] % p;
}