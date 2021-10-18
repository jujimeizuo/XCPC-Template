
// 暴力穷举查找

void square(int n)
{
    int ans = 0;
    for(int i = 1;i <= n / 2; i++)
        for(int j = 0;j <= i; j++)
            for(int k = 0;k <= j; k++)
                for(int q = 0;q <= k; q++)
                    if(i * i + j * j + k * k + q * q == n)
                        ans++;
}


// 动规背包优化

const int N = 1e5 + 10;

int dp[5][N];

void square() {
    dp[0][0] = 1;
    for(int i = 1;i <= 200; i++) {
        for(int j = 1;j <= 4; j++) {
            for(int k = 1;k <= 32768; k++) {
                if(i * i <= k)
                    dp[j][k] += dp[j - 1][k - i * i];
            }
        }
    }
}