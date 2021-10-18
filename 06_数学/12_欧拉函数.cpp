// 求解单个正整数的欧拉函数
int Get_phi(int n) {
    int ans = n;
    for(int i = 2;i * i <= n; i++) {
        if(n % i == 0) {
            ans = ans - ans / i;
            while(n % i == 0)
                n /= i;
        }
    }
    if(n > 1)
        ans = ans - ans / n;
    return ans;
}

// 埃拉托斯特尼筛求欧拉函数
int phi[10005];

void Euler_sieve(int n) {
    phi[1] = 1;
    for(int i = 2;i <= n; i++) {
        if(!phi[i]) {
            for(int j = i;j <= n; j += i)    {
                if(!phi[j])
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1); 
            }
        }
    }
}

// 欧拉筛求欧拉函数

const int N = 5e6 + 10;
bool is_prime[N];
int prime[N], phi[N], tot;

void Euler() {
    phi[1] = 1; is_prime[1] = true;
    for(int i = 2;i < N; i++){
        if(!is_prime[i]) {
            phi[i] = i - 1;
            prime[++tot] = i;
        }
        for(int j = 1;j <= tot && i * prime[j] < N; j++){
            is_prime[i * prime[j]] = true;
            if(i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
            else{
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
}