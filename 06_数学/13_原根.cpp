typedef long long ll;

vector<ll> YG;
ll p, n; // p是模数，n是p的欧拉函数值

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll quick_pow(ll a, ll b, ll p) ; 

ll phi(ll n) {
    ll ans = n;
    for(int i = 2;i * i <= n; i++) {
        if(n % i == 0) {
            ans = ans - ans / i;
            while(n % i == 0) {
                n /= i;
            }
        }
    }
    if(n > 1)
        ans = ans - ans / n;
    return ans;
}

vector<ll> PrimeFac(ll n) { // n的素因子
    vector<ll> fac;
    fac.clear();
    for(ll i = 2;i * i <= n; i++) {
        if(n % i == 0) {
            fac.push_back(i);
            while(n % i == 0)
                n /= i;
        }
    }
    if(n > 1)
        fac.push_back(n);
    return fac;
}

bool is_Protogen(ll p) { // 原根p = 2、4、p^k、2*p^k(p为非2的质数，k为任意数) 
    if(p == 2 || p == 4) return true;
    if(p <= 1 || p % 4 == 0) return false;
    ll num = 0;
    while(p % 2 == 0) // 2的倍数先筛掉
        p /= 2;
    for(int i = 3;i * i <= p; i++) { // p只能是一个非2的素数的倍数构成，否则没有原根
        if(p % i == 0) {
            num++;
            while(p % i == 0)
                p /= i;
        }
    }
    if(p > 1) num++;
    if(num == 1) return true;
    return false;
}

ll Protogen(ll p) {
    if(!is_Protogen(p)) // 先判断是否存在原根
        return -1;
    n = phi(p); 
    if(p == 2) return 1;
    if(p == 3) return 2;
    if(p == 4) return 3;
    vector<ll> fac = PrimeFac(n); // f(p)的素因子
    for(int i = 2;i <= p - 1; i++) {
        if(gcd(i, p) != 1) // n是模p的欧拉函数值，i要和n互质
            continue;
        bool flag = true; 
        for(ll j = 0;j < fac.size(); j++) {
            if(quick_pow(i, n / fac[j] , p) == 1)
                flag = 0;
        }
        if(flag) // i就是原根
            return i;
    }
    return -1;
}

void Sum_Protogen(ll k) { // 找出n的所有原根
    YG.push_back(k);
    for(int i = 2;i < n; i++) {
        if(gcd(i, n) == 1) // i要与f(n)互质
            YG.push_back(quick_pow(k, i, p));
    }
}

int main() {
    cin >> p;
    ll k = Protogen(p); // p的原根
    cout << k << endl;
    Sum_Protogen(k);
    for(int i = 0;i < YG.size(); i++) {
        cout << YG[i] << " ";
    }
    cout << endl;
    return 0;
}