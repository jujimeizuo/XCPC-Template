const int N = 5e6 + 10;
const ll mod = 1e9 + 7;

ll F[N], invn[N], invF[N];

void Init() {
    F[0] = F[1] = invn[0] = invn[1] = invF[0] = invF[1] = 1;
    for(int i = 2;i < N; i++){
        F[i] = F[i - 1] * i % mod;
        invn[i] = (mod - mod / i) * invn[mod % i] % mod;
        invF[i] = invF[i - 1] * invn[i] % mod;
    }
}
