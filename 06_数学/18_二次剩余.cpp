typedef long long ll;

typedef struct{
    ll x, y; // 把求出来的w作为虚部，则为a + bw
}num;

ll quick_pow(ll a, ll b, ll p) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans % p;
}


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
    return quick_pow(a, (p - 1) >> 1, p);
}

ll Cipolla(ll n, ll p) {// 输入a和p，是否存在x使得x^2 = a (mod p)，存在二次剩余返回x，存在二次非剩余返回-1     注意：p是奇质数
    n %= p;
    if(n == 0)
        return 0;
    if(p == 2)
        return 1;
    if(legendre(n, p) + 1 == p) // 二次非剩余
        return -1;
    
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

int main()
{
    ll n, p;
    cin >> n >> p;
    srand((unsigned)time(NULL));
    cout << Cipolla(n, p) << endl;
    return 0;
}