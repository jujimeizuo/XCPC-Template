// 求解a^x = b (mod c)，要求gcd(a, c) = 1， 不要求p为素数, x的范围是0 <= x <= p-1

#include <iostream>
#include <map>

using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;

int Hash[maxn], id[maxn], head[maxn], Next[maxn], cnt; // 链式前向星，比map快log，但是需要极大空间

struct HASH{
    void insert(ll x, ll y) {
        ll k = x % maxn;
        Hash[cnt] = x;
        id[cnt] = y;
        Next[cnt] = head[k];
        head[k] = cnt++;
    }

    ll query(ll x) {
        for(int i = head[x % maxn]; i != -1 ; i = Next[i]){
            if(Hash[i] == x)
                return id[i];
        }
        return -1;
    }
}HASH;

ll BSGS(ll a, ll b, ll c) {
    a %= c;
    b %= c;
    cnt = 1;
    if(b == 1)  return 0; 

    memset(head, -1, sizeof(head));

    ll m = ceil(sqrt((double)c)); // 向上取整
    ll x = 1, p = 1;

    for(ll j = 0;j < m; j++, p = p * a % c) {// 0 ~ m - 1
        HASH.insert(p * b % c, j); // 先枚举右边，把(b*a^j, j)放入hash中
    }

    for(ll i = 1, j ;i <= m; i++) { // 枚举a^im
        x = x * p % c;
        if((j = HASH.query(x)) != -1)
            return i * m - j; // 找到相匹配的哈希值
    }
    return -1;
}

int main() {
    ll a, b, c;
    cin >> a >> b >> c;
    cout << BSGS(a, b, c) << endl;
}
