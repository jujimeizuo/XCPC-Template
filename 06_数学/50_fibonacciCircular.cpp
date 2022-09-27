// 斐波那契循环节

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pdd;

#define INF 0x7f7f7f
#define mem(a,b) memset(a , b , sizeof(a))
#define FOR(i, x, n) for(int i = x;i <= n; i++)

const ll mod = 1e9 + 7;
const int maxn = 5e6 + 10;

bool is_prime[maxn];
ll prime[maxn];
int p;

void sieve() // 素数筛
{
    p = 0; 
    mem(is_prime, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2;i < maxn; i++)
    {
        if(is_prime[i])
        {
            prime[++p] = i;
            for(int j = i + i;j < maxn; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
}

ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

ll quick_pow(ll a, ll b)
{
    a %= mod;
    ll ans = 1;
    ll base = a;
    while(b)
    {
        if(b&1)
        {
            ans = ans * base % mod;
        }
        base = base * base % mod;
        b >>= 1;
    }
    return ans % mod;
}

ll num[maxn]; // 所有质数的循环节
ll f[maxn]; // 斐波那契数列

void Fib_Cyclic_node()
{
    num[1] = 3;
    for(int i = 2;i <= p; i++) // 找每个素数的循环节num[1~p]
    {
        f[1] = 1;
        f[2] = 2;
        int x = 3;
        while(true)
        {
            f[x] = f[x - 1] + f[x - 2];
            f[x] %= prime[i];
            if(f[x] == 1 && f[x - 1] == 0) // f[x] % prime[i] == f[1]
                break;
            x++;
        }
        num[i] = x;
    }

    ll n;
    cin >> n; // 如果是质数，那循环节就是num[n] ；  如果是合数，那循环节就是n的素因子的最小公倍数
    ll ans = 1;
    ll x;
    for(int i = 1;i <= p; i++)
    {
        if(n % prime[i] == 0)
        {
            x = 0;
            while(n % prime[i] == 0)
            {
                n /= prime[i];
                x++;
            }
        }
        ll k = num[i] * quick_pow(prime[i], x - 1);
        ans = ans * k / gcd(ans, k); // 最小公倍数
    }
    cout << ans << endl; // 最小循环节
}

// 广义斐波那契循环节

// fib(n) = a * fib(n - 1) + b * fib(n - 2)
// fib(1) = c   fib(2) = d
// 求f(n) mod p的循环节     
//c = a * a - 4b是模p的二次剩余时枚举p-1的因子，否则枚举(p+1)(p-1)的因子

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pdd;

#define INF 0x7f7f7f
#define mem(a,b) memset(a , b , sizeof(a))
#define FOR(i, x, n) for(int i = x;i <= n; i++)

ll fac[2][505];
ll cnt, ct;

ll pri[6] = {2, 3, 7, 109, 167, 500000003};
ll num[6] = {4, 2, 1, 2, 1, 1};

const ll mod = 1e9 + 7;
const int maxn = 5e6 + 10;

struct Matrix{
    ll m[2][2];
};

Matrix A;

Matrix I = {1, 0, 0 , 1}; // 单位矩阵

Matrix multi(Matrix a, Matrix b) // 矩阵乘法
{
    Matrix C;
    for(int i = 0;i < 2; i++)
    {
        for(int j = 0;j < 2; j++)
        {
            C.m[i][j] = 0;
            for(int k = 0;k < 2; k++)
            {
                C.m[i][j] = (C.m[i][j] + a.m[i][k] * b.m[k][j] % mod) % mod; 
            }
            C.m[i][j] %= mod;
        }
    }
    return C;
}

Matrix quick_Matrix(Matrix a, ll b) // 矩阵快速幂
{
    Matrix ans = I, base = a;
    while(b)
    {
        if(b & 1)
        {
            ans = multi(a, base);
        }
        base = multi(base, base);
        b >>= 1;
    }
    return ans;
}

ll quick_pow(ll a, ll b) ;

ll legendre(ll a, ll p) // 勒让德符号 = {1, -1, 0}
{
    ll k = quick_pow(a, (p - 1) >> 1);
    if(k == 1)
        return 1;
    else 
        return -1;
}

void DFS(int dept,ll product = 1)
{
    if(dept == cnt)
    {
        fac[1][ct++] = product;
        return;
    }
    for(int i=0; i<=num[dept]; i++)
    {
        DFS(dept+1,product);
        product *= pri[dept];
    }
}

bool Fib_node(Matrix a, ll n) // n是否为循环节
{
    Matrix ans = quick_Matrix(a, n);
    return (ans.m[0][0] == 1 && ans.m[0][1] == 0 && ans.m[1][0] == 0 && ans.m[1][1] == 1); // 是否为单位矩阵I
}

ll Fib_Cyclic_node(ll a, ll b, ll c, ll d) // 广义斐波那契循环节斐波那契循环节
{
    fac[0][0] = 1;
    fac[0][1] = 2;
    fac[0][3] = 500000003;
    fac[0][3] = 1000000006;
    ll c = a * a - 4 * b;
    A.m[0][0] = a;
    A.m[0][1] = b;
    A.m[1][0] = 1;
    A.m[1][1] = 0; 
    if(legendre(c, mod) == 1) // c是否为1e9+7的二次剩余
    {
        for(int i = 0;i < 4; i++)
        {
            if(Fib_node(A, fac[0][i]))
                return fac[0][i];
        }
    }
    else
    {
        ct = 0;
        cnt = 6;
        DFS(0, 1);
        sort(fac[1], fac[1] + ct);
        for(int i = 0;i < ct; i++)
        {
            if(Fib_node(A, fac[1][i]))
                return fac[1][i];  
        }
    }
    
}

int main()
{
    ll a, b, c, d;
    cin >> a >> b >> c >> d; 
    ll n = Fib_Cyclic_node(a, b, c, d); // 广义斐波那契循环节循环节长度
    cout << n << endl;
}

