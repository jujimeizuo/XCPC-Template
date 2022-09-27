//四边形优化区间dp(n^3 -> n^2)
//a < b < c < d, f[l][r] = min(f[l][k] + f[k + 1][r] + cost(l, r))
//1. cost(b, c) <= cost(a, d)
//2. cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c), 即交叉小于包含

template <typename T>
void quadrilateralOptimization() {
    for (int len = 2; len <= n; len++) {
        for (int l = 1, r; l + len - 1 <= n; l++) {
            r = l + len - 1;
            mn[l][r] = 0x3f3f3f3f;
            for (int k = m[l][r - 1]; k <= m[l + 1][r]; k++)
                if (mn[l][k] + mn[k + 1][r] + cost(l, r) < mn[l][r]) {
                    mn[l][r] = mn[l][k] + mn[k + 1][r] + cost(l, r);
                    m[l][r] = k;
                }
        }
    }
}
