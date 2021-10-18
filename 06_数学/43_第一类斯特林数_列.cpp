#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define mod 167772161
#define MAXN 531072
#define Gi 3

int quick_pow (int a,int b,int c)
{
    int res = 1;
    while (b){
        if (b & 1) res = 1ll * res * a % c;
        a = 1ll * a * a % c;
        b >>= 1;
    }
    return res;
}

int limit = 1,l,r[MAXN];

void NTT (int *a,int type)
{
    for (Int i = 0;i < limit;++ i) if (i < r[i]) swap (a[i],a[r[i]]);
    for (Int mid = 1;mid < limit;mid <<= 1){
        int Wn = quick_pow (Gi,(mod - 1) / (mid << 1),mod);
        if (type == -1) Wn = quick_pow (Wn,mod - 2,mod);
        for (Int R = mid << 1,j = 0;j < limit;j += R){
            for (Int k = 0,w = 1;k < mid;++ k,w = 1ll * w * Wn % mod)
            {
                int x = a[j + k],y = 1ll * w * a[j + k + mid] % mod;
                a[j + k] = (x + y) % mod,a[j + k + mid] = (x + mod - y) % mod;
            }
        }
    } 
    if (type == 1) return ;
    int Inv = quick_pow (limit,mod - 2,mod);
    for (Int i = 0;i < limit;++ i) a[i] = 1ll * a[i] * Inv % mod;
}

int c[MAXN];

void Solve (int len,int *a,int *b)
{
    if (len == 1) return b[0] = quick_pow (a[0],mod - 2,mod),void ();
    Solve ((len + 1) >> 1,a,b);
    limit = 1,l = 0;
    while (limit < (len << 1)) limit <<= 1,l ++;
    for (Int i = 0;i < limit;++ i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    for (Int i = 0;i < len;++ i) c[i] = a[i];
    for (Int i = len;i < limit;++ i) c[i] = 0;
    NTT (c,1);NTT (b,1);
    for (Int i = 0;i < limit;++ i) b[i] = 1ll * b[i] * (2 + mod - 1ll * c[i] * b[i] % mod) % mod;
    NTT (b,-1);
    for (Int i = len;i < limit;++ i) b[i] = 0;
}

void deravitive (int *a,int n){
    for (Int i = 1;i <= n;++ i) a[i - 1] = 1ll * a[i] * i % mod;
    a[n] = 0;
}

void inter (int *a,int n){
    for (Int i = n;i >= 1;-- i) a[i] = 1ll * a[i - 1] * quick_pow (i,mod - 2,mod) % mod;
    a[0] = 0;
}

int b[MAXN];

void Ln (int *a,int n){
    memset (b,0,sizeof (b));
    Solve (n,a,b);deravitive (a,n);
    while (limit <= n) limit <<= 1,l ++;
    for (Int i = 0;i < limit;++ i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    NTT (a,1),NTT (b,1);
    for (Int i = 0;i < limit;++ i) a[i] = 1ll * a[i] * b[i] % mod;
    NTT (a,-1);
    inter (a,n);
    for (Int i = n + 1;i < limit;++ i) a[i] = 0;
}

int F0[MAXN];

void Exp (int *a,int *B,int n){
    if (n == 1) return B[0] = 1,void ();
    Exp (a,B,(n + 1) >> 1);
    for (Int i = 0;i < limit;++ i) F0[i] = B[i];
    Ln (F0,n);
    F0[0] = (a[0] + 1 + mod - F0[0]) % mod;
    for (Int i = 1;i < n;++ i) F0[i] = (a[i] + mod - F0[i]) % mod;
    NTT (F0,1);NTT (B,1);
    for (Int i = 0;i < limit;++ i) B[i] = 1ll * F0[i] * B[i] % mod;
    NTT (B,-1);
    for (Int i = n;i < limit;++ i) B[i] = 0;
}

int read ()
{
    int x = 0;char c = getchar();int f = 1;
    while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
    while (c >= '0' && c <= '9'){x = (int)((int)(x << 3) % mod + (int)(x << 1) % mod + c - '0') % mod;c = getchar();}
    return x * f;
}

void write (int x)
{
    if (x < 0){x = -x;putchar ('-');}
    if (x > 9) write (x / 10);
    putchar (x % 10 + '0');
}

int n,k;
int fac[MAXN],A[MAXN],B[MAXN];

signed main()
{
	n = read (),k = read ();
	for (Int i = 0;i < n;++ i) A[i] = quick_pow (i + 1,mod - 2,mod);
	Ln (A,n);
	for (Int i = 0;i < n;++ i) A[i] = 1ll * A[i] * k % mod;
	Exp (A,B,n);fac[0] = 1;
	for (Int i = 1;i <= max (n,k);++ i) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (Int i = n;i >= k;-- i) B[i] = B[i - k];
	for (Int i = 0;i < k;++ i) B[i] = 0;int Inv = quick_pow (fac[k],mod - 2,mod);
	for (Int i = 0;i <= n;++ i) write (1ll * B[i] * fac[i] % mod * Inv % mod),putchar (' ');
	putchar ('\n');
    return 0;
}
