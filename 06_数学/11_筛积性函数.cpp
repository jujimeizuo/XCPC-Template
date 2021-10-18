//只需要计算f(p ^ k)即可
//其余的都可以通过积性函数的性质来计算

int vis[N], prime[N], num;
int f[N], low[N];

void makeF(int siz) {//f为积性函数
    num = 0, low[1] = f[1] = 1;
    for (int i = 2; i <= siz; i++) {
        if (!vis[i]) prime[++num] = i, low[i] = i, f[i] = ...;//这里是f(p)的答案
        for (int j = 1; j <= num && i * prime[j] <= siz; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                low[i * prime[j]] = low[i] * prime[j];
                if(low[i] == i) {//i = prime[j] ^ k
                    //只需要这里算一下
                    //考虑 p ^ 1 , p ^ 2, p ^ 3...
                }
                else f[i * prime[j]] = 1ll * f[i / low[i]] * f[prime[j] * low[i]] % mod;
                break;
            }
            low[i * prime[j]] = prime[j];
            f[i * prime[j]] = 1ll * f[i] * f[prime[j]] % mod;
        }
    }
}

