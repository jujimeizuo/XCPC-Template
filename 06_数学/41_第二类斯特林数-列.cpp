// 把n个不同元素划分成m个相同的集合（不能有空集）的方案数。

// k!\sum_{i=0}\frac{{i,k}x^i}{i!}=(e^x-1)^k

const int N = 6e5 + 10;
const ll mod = 167772161;

ll quick_pow(ll a, ll b) ;

const ll G = 3;
const ll invG = quick_pow(G, mod - 2);

int tr[N];
bool flag;

void NTT(ll *A, int len, int type) ;
void mul(ll *a, ll *b, int len) ;
void Get_Der(ll *f, ll *g, int len) ;
void Get_Int(ll *f, ll *g, int len) ;
void Get_Inv(ll *f, ll *g, int n) ;
void Get_Ln(ll *f, ll *g, int n) ;
void Get_Exp(ll *f, ll *g, int n) ;
void Get_Pow(ll *f, ll *g, int n, ll k1, ll k2);

ll a[N], ans[N];

ll F[N], invF[N], inv[N];
void init() ;


void solve() {
    init();
    int n; ll k; cin >> n >> k; n++;
    if(k >= mod) flag = 1;
    for(int i = 1;i < n; i++) a[i] = invF[i];
    Get_Pow(a, ans, n, k % mod, k % (mod - 1));
    for(int i = 0;i < n; i++) {
        cout << ans[i] * invF[k] % mod * F[i] % mod << (i == n - 1 ? endl : " ");
    }
}
