// 倍增思想加DP优化

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int a[N];
int dp[N][105];

// 一维ST表
void One_ST(){
    int n;
    cin >> n;
    for(int i = 1;i <= n; i++) {
        cin >> a[i];
        dp[i][0] = a[i];

        // cin >> dp[i][0];
    }

    for(int j = 1;j <= log2(n); j++) {
        for(int i = 1;i <= n; i++) {
            if(i + (1 << (j - 1)) <= n)
                dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }

    int T;
    cin >> T;
    while(T--) {
        int l, r;
        cin >> l >> r;
        int len = log2(r - l + 1);
        int k = max(dp[l][len], dp[r - (1 << len) + 1][len]);
        cout << k << endl;
    }
}

// 二维ST表
int f[105][105][105];

void Two_ST() {
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= m; j++){
            cin >> a[i];
            f[i][j][0] = a[i];
        }

// 大矩阵分成四个小矩阵求最值

    for(int k = 1;k < log2(n); k++) {
        for(int i = 1;i <= n; i++) {
            for(int j = 1;j <= m; j++) {
                if((i + (1 << (k - 1)) <= n) && (j + (1 << (k - 1)) <= m))
                    f[i][j][k] = max(max(f[i][j + (1 << (k - 1))][k - 1], f[i + (1 << (k - 1))][j][k - 1]), max(f[i][j][k - 1], f[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]));
        }
    }

    int T;
    cin >> T;
    while(T--) {
        int l, r, k;
        cin >> l >> r >> k; 
        int len = log2(k); 
        int s = max(max(f[l][r][len], f[l + k - (1 << len)][r + k - (1 << len)][len]), max(f[l + k - (1 << len)][r][len], f[l][r + k - (1 << len)][len]));
    }

}