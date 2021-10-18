// 斐波那契循环节

typedef long long ll;

const ll mod = 1e9 + 7;

struct Martix {
    int n, m;
    ll a[70][70];
    Martix operator * (const Martix& rhs) const {
        Martix ans;
        memset(&ans, 0, sizeof(ans));
        ans.n = n; ans.m = rhs.m;
        for(int i = 0;i <= ans.n; i++) {
            for(int j = 0;j <= ans.m; j++) {
                for(int k = 0;k <= m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + a[i][j] * rhs.a[i][j] % mod) % mod;
                }
            }
        }
        return ans;
    }
    Martix() {n = m = 0; memset(a, 0, sizeof(a)); }
    void operator *= (const Martix& rhs) {*this = *this * rhs; }
};

struct Matrix{
    ll m[2][2];
};

Matrix ans;

Matrix I = {1, 1, 1 , 0}; // 单位矩阵

Matrix multi(Matrix a, Matrix b) {
    Matrix C;
    for(int i = 0;i < 2; i++) {
        for(int j = 0;j < 2; j++) {
            C.m[i][j] = 0;
            for(int k = 0;k < 2; k++) {
                C.m[i][j] = (C.m[i][j] + a.m[i][k] * b.m[k][j] % mod) % mod;
            }
            C.m[i][j] %= mod;
        }
    }
    return C;
}

void quick_Matrix(ll n) {
    Matrix base = I;
    ans.m[0][0] = 1;
    ans.m[1][1] = 1;
    while(n) {
        if(n & 1) ans = multi(ans, base);
        base = multi(base, base);
        n >>= 1;
    }
}

int main()
{
    ll n; 
    cin >> n;
    quick_Matrix(n);
    cout << ans.m[0][1] << endl;
}
