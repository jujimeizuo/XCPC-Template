// {n,m}->n个不同元素划分成m个相同的集合中（不能有空集）的方案数。

// {n,m}={n-1,m-1}+k{n-1,m}

// {n,m}=\sum_{i=0}^n \frac{i^n}{i!} * {(-1)^{m-i}}{(m-i)!}

const int N = 1e6 + 10;
const ll mod = 167772161;

ll F[N], invF[N];
void init() ;

ll qpow(ll a, ll b, ll mod) ;

const ll G = 3;
const ll invG = qpow(G, mod - 2, mod);
int tr[N];

void NTT(ll *A, int len, int type) ;
void mul(ll *a, ll *b, int n) ;

ll a[N], b[N];

void solve() {
    init();
    int n; cin >> n;
    for(int i = 0;i <= n; i++) {
        a[i] = qpow(i, n, mod) * invF[i] % mod;
        if(i & 1) b[i] = mod - invF[i];
        else b[i] = invF[i];
    }
    mul(a, b, 2 * n);
    for(int i = 0;i <= n; i++) cout << a[i] << (i == n ? endl : " ");
}
