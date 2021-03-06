// 输出0~n中存在49的个数

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pdd;

#define INF 0x7f7f7f
#define mem(a, b) memset(a , b , sizeof(a))
#define FOR(i, x, n) for(int i = x;i <= n; i++)

// const ll mod = 1e9 + 7;
// const int maxn = 1e5 + 10;
// const double eps = 1e-6;


int dight[105];
ll dp[105][10]; // 第一维是数位，第二维是上一个数位上的数字

ll DFS(int pos, int pre, bool limit) // pos为该数位，pre为上一数位上的数字，limit表示是否上界，上一位pre是否已到达最大
{
    if(pos == 0) return 1; // 每一数位都遍历完，说明这一个数是可取的
    if(!limit && dp[pos][pre] != -1) return dp[pos][pre]; // 剪枝，记忆化搜索

    int up = limit ? dight[pos] : 9; // 如果有上界，则pos该数位只能取到dight[pos]这么大

    ll ans = 0;

    for(int i = 0;i <= up; i++) // 遍历该数位1~up的每一位
    {
        if(pre == 4 && i == 9) // 如果上一位是4且这一位是9，那就组成了49，不可取
            continue;
        ans += DFS(pos - 1, i, limit && i == dight[pos]); // ans+搜索下一位
    }

    if(!limit)
        dp[pos][pre] = ans;

    return ans;
}

ll sum(ll n) // 找出n中没有49的数并返回
{
    int k = 0;
    while(n)
    {
        dight[++k] = n % 10; // 从个位开始，把每一个数位上的数字都记录下来
        n /= 10;
    }

    return DFS(k, 0, 1); // 从最高位开始，前一位为前导零且没有限制
}

void solve()
{
    mem(dp, -1); // 初始化所有的dp
    int T;
    cin >> T;
    while(T--)
    {
        ll n;
        cin >> n;
        cout << n - sum(n) + 1 << endl; // +1是因为sum(n)把0也算进去了
    }
}