// 乘法逆元的线性递推，复杂度O(n)

typedef long long ll;

ll inv[3000005] = {0 , 1}; //n等于1时，关于mod的逆元就为1

int main()
{
    ll n, mod;
    cin >> n >> mod;
    cout << 1 << endl;
    for(int i = 2;i <= n; i++)
    {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
        cout << inv[i] << endl;
    }
    return 0;
}