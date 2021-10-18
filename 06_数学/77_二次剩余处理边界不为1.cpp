
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = acos(-1);
const int N = 1e5 + 10;


struct Complex {
    double x, y;
    Complex(double a = 0, double b = 0): x(a), y(b) {}
    Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
    Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
    Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Complex conj() { return Complex(x, -y); }
} w[N];

ll mod, inv2;
int tr[N];
ll F[N], G[N];

ll quick_pow(ll a, ll b) ;

typedef struct{
    ll x, y; // 把求出来的w作为虚部，则为a + bw
}num;

num num_mul(num a, num b, ll w, ll p) {// 复数乘法
    num ans = {0, 0};
    ans.x = (a.x * b.x % p + a.y * b.y % p * w % p + p) % p;
    ans.y = (a.x * b.y % p + a.y * b.x % p + p) % p;
    return ans;
} 

ll num_pow(num a, ll b, ll w, ll p) { // 复数快速幂
    num ans = {1, 0};
    while(b) {
        if(b & 1)
            ans = num_mul(ans, a, w, p);
        a = num_mul(a, a, w, p);
        b >>= 1;
    }
    return ans.x % p;
}

ll legendre(ll a, ll p) { // 勒让德符号 = {1, -1, 0}
    return quick_pow(a, (p - 1) >> 1);
}

ll Cipolla(ll n, ll p) {// 输入a和p，是否存在x使得x^2 = a (mod p)，存在二次剩余返回x，存在二次非剩余返回-1     注意：p是奇质数
    n %= p;
    if(n == 0)
        return 0;
    if(p == 2)
        return 1;
    ll a, w; 
    
    while(true) {// 找出a，求出w，随机成功的概率是50%，所以数学期望是2
        a = rand() % p;
        w = ((a * a - n) % p + p) % p;
        if(legendre(w, p) + 1 == p) // 找到w，非二次剩余条件
            break;
    }
    num x = {a, 1};   
    return num_pow(x, (p + 1) >> 1, w, p) % p; // 计算x,一个解是x，另一个解是p-x，这里的w其实要开方，但是由拉格朗日定理可知虚部为0，所以最终答案就是对x的实部用快速幂求解
}

int getLen(int n) ;

void FFT(Complex *A, int len) ;

inline void MTT(ll *x, ll *y, ll *z, int len) ;

void Get_Inv(ll *f, ll *g, int n) ;

void Get_Sqrt(ll *f, ll *g, int n) {
    if(n == 1) { ll t = Cipolla(f[0], mod); g[0] = min(mod - t, t); return ; }
    Get_Sqrt(f, g, (n + 1) >> 1);

    int len = getLen(n);
    static ll c[N], invg[N];
    for(int i = 0;i < len; i++) c[i] = i < n ? f[i] : 0;
    Get_Inv(g, invg, n);
    MTT(c, invg, c, len);
    for(int i = 0;i < n; i++) g[i] = inv2 * (c[i] + g[i]) % mod;
    for(int i = n;i < len; i++) g[i] = 0;
    for(int i = 0;i < len; i++) c[i] = invg[i] = 0;
}

int main() {
    inv2 = quick_pow(2, mod - 2);
    int n;
    cin >> n;
    for(int i = 0;i < n; i++) cin >> F[i];
    Get_Sqrt(F, G, n);
    for(int i = 0;i < n; i++) cout << G[i] << " ";
}