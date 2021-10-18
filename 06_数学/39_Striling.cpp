typedef long long ll;
const int N = 20;

// 第一类斯特林数
ll S1[N][N];
void Stirling1() {
    S1[0][0] = 1;
    for(int i = 1;i < N; i++) {
        for(int j = 1;j <= i; j++) {
            S1[i][j] = S1[i - 1][j - 1] + (i - 1) * S1[i - 1][j];
        }
    }
}

// 第二类斯特林数
ll S2[N][N];
void Stirling2() {
    S2[0][0] = 1;
    for(int i = 1;i < N; i++) {
        for(int j = 1;j <= i; j++) {
            S2[i][j] = S2[i - 1][j - 1] + j * S2[i - 1][j];
        }
    } 
}