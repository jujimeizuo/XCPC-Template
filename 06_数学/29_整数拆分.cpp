#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

//递归
ll PartitionCount(ll n, ll m) {
    if(n == 1 || m == 1)  return 1;
    else if(n < m) return PartitionCount(n , n);
    else if(n == m) return PartitionCount(n , n - 1) + 1;
    else return PartitionCount(n - m , m) + PartitionCount(n , m - 1);
}

//DP
ll dp[1005][1005];

void Partition_DP(ll n, ll m) {
    for(ll i = 1;i <= n + 1; i++) {
        for(ll j = 1;j <= m + 1; j++) {
            if(i == 1 || j == 1) dp[i][j] = 1;
            else if(i == j) dp[i][j] = 1 + dp[i][j - 1];
            else if(i < j) dp[i][j] = dp[i][i];
            else dp[i][j] = dp[i - j][j] + dp[i][j - 1];
         }
     }
}