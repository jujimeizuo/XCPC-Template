const int N = 1e5 + 10;
bool is_prime[N];
int prime[N], mu[N], cnt;

void makeMobius() {
    mu[1] = 1; is_prime[0] = is_prime[1] = true;
    for(int i = 2;i < N; i++) {
        if (!is_prime[i]) {
            mu[i] = -1;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            is_prime[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}
