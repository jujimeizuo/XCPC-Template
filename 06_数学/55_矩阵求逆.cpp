//原始矩阵A[0, n - 1][0, n - 1]
//右边一个单位阵I, 在a[0, n - 1][n, (n << 1) - 1]
//将左边A变成单位阵时，右边的I变为A^-1

ll a[MAX][MAX];
bool Gauss(int n) {
    for (int i = 0, r; i < n; i++) {
        r = i;
        for (int j = i + 1; j < n; j++)
            if (a[j][i] > a[r][i]) r = j;
        if (r != i) swap(a[i], a[r]);
        if (!a[i][i]) return false;//无解

        ll inv = qpow(a[i][i], mod - 2);
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            ll t = a[k][i] * inv % mod;
            for (int j = i; j < (n << 1); j++)
                a[k][j] = (a[k][j] - t * a[i][j] % mod + mod) % mod;
        }
        for (int j = 0; j < (n << 1); j++) a[i][j] = a[i][j] * inv % mod;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a[i][i + n] = 1;
        for (int j = 0; j < n; j++)
            scanf("%lld", &a[i][j]);
    }
    if(Gauss(n)) {
        for(int i = 0;i < n; i++) {
            for(int j = n;j < n * 2; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }
    else cout << "No Solution" << endl;
}
