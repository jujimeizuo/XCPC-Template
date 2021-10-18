const int N = 1e6 + 10;
bool is_prime[N]; //is_prime[i]为true时，i为素数
int prime[N], cnt = 0;

void sieve(int n) {
    is_prime[0] = is_prime[1] = 1; //0和1都不是素数
    for(int i = 2;i <= sqrt(n); i++) {
        if(!is_prime[i]) {
            for(int j = 2 * i;j <= n; j += i) {
                is_prime[j] = 1; //删除所有的素数的倍数
            }
        }
    }
}
    

void euler() {
    is_prime[0] = is_prime[1] = 1;
    for(int i = 2;i < N; i++) {
        if(!is_prime[i]) {
            prime[++cnt] = i;
        }
        for(int j = 1;j <= cnt && prime[j] * i < N; j++) {
            is_prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
