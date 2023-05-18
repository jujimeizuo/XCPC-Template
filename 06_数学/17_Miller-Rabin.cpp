// 二次探测定理：对素数p,满足x^2≡1(modp)的小于p的正整数解x只有1或p−1.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 7;
const int times = 10;

ll ksc(ll a, ll b, ll mod)  {
    ll ans = 0;
    while(b > 0) {
        if(b & 1) {
            ans = (ans + a) % mod;
        }
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ans;
}

ll quick_pow(ll a, ll b, ll mod) {
    ll ans = 1, base = a;
    while(b != 0) {
        if(b & 1) {
            ans = ans * base % mod;
        }
        base = base * base % mod;
        b >>= 1;
    }
    return ans;
}

bool Miller_Pabin(ll n)//Miller测试的主体结构
{
    if(n < 2) return false;
    if(n == 2) return true;
    if(n & 1 == 0) return false;//对于偶数的优化
    ll k = 0,u = n - 1;//p为Miller测试的k，u为Miller测试的m
    
    while(u & 1 == 0){ // 把x拆成u*2^k
        u >>= 1;
        k++;
    }
    srand(time(NULL));

    ll x, pre; // pre为上次探测的x的值

    for(int i = 1;i <= times; i++) {
        x = rand() % (n - 1) + 1;
        x = quick_pow(x, u, n); // 先求出x^u(mod n)
        pre = x;
        for(int j = 1;j <= k; j++) {
            x = ksc(x, x, n);
            if(x == 1 && pre != 1 && pre != n - 1)
                return false;
            pre = x;
        }
        if(x != -1)
        return false;
    }
    return true;
}
 
int main() {
    ll n; cin >> n;
    cout << (Miller_Pabin(n) ? "Prime" : "Not a Prime") << endl;
}