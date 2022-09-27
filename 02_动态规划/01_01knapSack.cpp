template <typename T>
T knapSack(const std::vector<int>& v, const std::vector<T>& w, int V) {
    int n = (int) v.size();
    std::vector<T> dp(V + 1);
    for (int i = 0; i < n; i++) {
        for (int j = V; j >= v[i]; j--) {
            dp[j] = std::max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    return dp.back();
}