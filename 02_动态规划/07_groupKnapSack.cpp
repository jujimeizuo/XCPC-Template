template <typename T>
T groupKnapSack(const std::vector<std::vector<std::array<int, 2>>>& groups, int V) {
    std::vector<T> dp(V + 1);
    for (auto& group : groups) {
        int n = group.size();
        for (int j = V; j >= 0; j--) {
            for (auto& [v, w] : group) {
                if (j >= v) {
                    dp[j] = std::max(dp[j], dp[j - v] + w);
                }
            }
        }
    }
    return dp.back();
}