// 倍增思想加DP优化

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int a[N];


template <typename T, class F = std::function<T(const T&, const T&)>>
class SparseTable {
public:
    int n;
    std::vector<std::vector<T>> mat;
    F func;
 
    SparseTable(const std::vector<T>& a, const F& f) : func(f) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
 
    T get(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }
};

// 二维ST表
int f[105][105][105];

void Two_ST() {
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= m; j++){
            cin >> a[i];
            f[i][j][0] = a[i];
        }

// 大矩阵分成四个小矩阵求最值

    for(int k = 1;k < log2(n); k++) {
        for(int i = 1;i <= n; i++) {
            for(int j = 1;j <= m; j++) {
                if((i + (1 << (k - 1)) <= n) && (j + (1 << (k - 1)) <= m))
                    f[i][j][k] = max(max(f[i][j + (1 << (k - 1))][k - 1], f[i + (1 << (k - 1))][j][k - 1]), max(f[i][j][k - 1], f[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]));
        }
    }

    int T;
    cin >> T;
    while(T--) {
        int l, r, k;
        cin >> l >> r >> k; 
        int len = log2(k); 
        int s = max(max(f[l][r][len], f[l + k - (1 << len)][r + k - (1 << len)][len]), max(f[l + k - (1 << len)][r][len], f[l][r + k - (1 << len)][len]));
    }

}