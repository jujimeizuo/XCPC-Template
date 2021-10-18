// 统计(a,b)到(c,d)这个矩阵中的所有0子矩阵

const int N = 50 + 10;
int sum[N][N];
int Q[N][N][N][N];

void solve() {
    int n, m, q; cin >> n >> m >> q;
    for(int i = 1;i <= n; i++) {
        string s; cin >> s;
        for(int j = 1;j <= m; j++) {
            sum[i][j] = (s[j - 1] - '0') + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    for(int a = 1;a <= n; a++) {
        for(int b = 1;b <= m; b++) {
            for(int c = a;c <= n; c++) {
                for(int d = b;d <= m; d++) {
                    if(sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1] == 0) {
                        Q[a][b][c][d]++;
                    }
                }
            }
        }
    }

    for(int a = n;a >= 1; a--) {
        for(int b = m;b >= 1; b--) {
            for(int c = 1;c <= n; c++) {
                for(int d = 1;d <= m; d++) {
                    Q[a][b][c][d] += Q[a + 1][b][c][d];
                }
            }
        }
    }

    for(int a = n;a >= 1; a--) {
        for(int b = m;b >= 1; b--) {
            for(int c = 1;c <= n; c++) {
                for(int d = 1;d <= m; d++) {
                    Q[a][b][c][d] += Q[a][b + 1][c][d];
                }
            }
        }
    }

    for(int a = n;a >= 1; a--) {
        for(int b = m;b >= 1; b--) {
            for(int c = 1;c <= n; c++) {
                for(int d = 1;d <= m; d++) {
                    Q[a][b][c][d] += Q[a][b][c - 1][d];
                }
            }
        }
    }

    for(int a = n;a >= 1; a--) {
        for(int b = m;b >= 1; b--) {
            for(int c = 1;c <= n; c++) {
                for(int d = 1;d <= m; d++) {
                    Q[a][b][c][d] += Q[a][b][c][d - 1];
                }
            }
        }
    }

    while(q--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << Q[a][b][c][d] << endl;
    }
}
