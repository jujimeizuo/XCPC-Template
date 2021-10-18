int is_prime[N], prime[N], cnt, phi[N];
void makePhi() {
    phi[1] = 1, cnt = 0;
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            is_prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}
