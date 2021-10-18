
// NTT求法，任意模数复杂度较高
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

ll mod, g;
int tr[N];
ll F[N], G[N];

ll quick_pow(ll a, ll b) ;

int getLen(int n) ;

void NTT(ll *a, int len, int opt) ;

void mul(ll *a, ll *b, ll *z, int n) ;

void Get_Inv(ll *f, ll *g, int n) ;

void ChaiFen(ll *f, ll *g, int n) {
    int len = getLen(n);
    for(int i = 0;i < len; i++) {
        ll a = 1ll * i * (3 * i - 1) / 2; ll b = 1ll * i * (3 * i + 1) / 2;
        if(a > len && b > len) break;
        ll tmp;
        if(i & 1) tmp = mod - 1;
        else tmp = 1;
        if(a < len) f[a] = tmp;
        if(b < len) f[b] = tmp;
    }

    Get_Inv(f, g, n);
}

int main() {
    int n;
    cin >> n;
    ChaiFen(F, G, n);
    for(int i = 1;i <= n; i++) cout << G[i] << endl;
}
