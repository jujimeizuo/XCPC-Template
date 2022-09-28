template <typename T>
T twoDimensionalKnapSack(const std::vector<int>& v, const std::vector<int>& m, const std::vector<T>& w, int V, int M) {
    int n = (int) v.size();
    std::vector<std::vector<T>> dp(V + 1, std::vector<T>(M + 1));
    for (int i = 0; i < n; i++) {
        for (int j = V; j >= v[i]; j--) {
            for (int k = M; k >= m[i]; k--) {
                dp[j][k] = std::max(dp[j][k], dp[j - v[i]][k - m[i]] + w[i]);
            }
        }
    }
    return dp.back().back();
}