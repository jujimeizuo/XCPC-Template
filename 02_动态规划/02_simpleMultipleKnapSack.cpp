template <typename T>
T simpleMultipleKnapSack(const std::vector<int>& v, const std::vector<T>& w, const std::vector<int>& cnt, int V) {
    int n = (int) v.size();
    std::vector<T> dp(V + 1);
    for (int i = 0; i < n; i++) {
        for (int j = V; j >= 0; j--) {
            for (int k = 1; k <= cnt[i]; k++) {
                if (j - k * v[i] < 0) break ;
                dp[j] = std::max(dp[j], dp[j - k * v[i]] + k * w[i]);
            }
        }
    }
    return dp.back();
}