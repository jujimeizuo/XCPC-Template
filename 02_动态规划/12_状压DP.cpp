// 杭电1565

int n;
int a[22][22];
int dp[22][1 << 18]; // 第一维是行数，第二位是该行的方案数，继承了前面所有行数的方案数
int tot[1 << 18]; // 方案数

int calc(int i, int k)
{
    int cnt = 1, res = 0;
    while(k)
    {
        if(k & 1) res += a[i][cnt];
        k >>= 1;
        cnt++;
    }
    return res;
}

void solve()
{
    while(cin >> n) {
        mem(dp, 0);
        int cnt = 0;

        for (int i = 0; i <= (1 << n) - 1; i++) { // 预处理
            if ((i & (i >> 1)) == 0) // 判断i这个二进制是否满足相邻没有两个1的条件
                tot[++cnt] = i;
        }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> a[i][j];

        for (int i = 1; i <= n; i++) { // 行遍历
            for (int k = 1; k <= cnt; k++) { // 第i行k的二进制排列的数，与下面的j进行&
                int val = calc(i, tot[k]); // 计算k的二进制中1所在a数组里的权值
                for (int j = 1; j <= cnt; j++) { // 第i-1行j的二进制排列的数，与上面的k进行&并进行状态转移
                    if ((tot[j] & tot[k]) == 0)
                        dp[i][k] = max(dp[i][k], dp[i - 1][j] + val);
                }
            }
        }

        int ans = -1;
        for (int j = 1; j <= cnt; j++)
            ans = max(ans, dp[n][j]);

        cout << ans << endl;
    }
}



