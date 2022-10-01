template <typename T>
T groupKnapSack(const std::vector<std::vector<std::array<int, 2>>>& groups, int V) {
    std::vector<T> dp(V + 1);
    for (auto& group : groups) {
        for (int j = V; j >= 0; j--) {
            for (auto& [v, w] : group) {
                if (j >= v) {
                    dp[j] = std::max(dp[j], dp[j - v] + w);
                }
                /*
                 if (j >= v) {
                    // from groups[i], ensure dp[i][j-v] has at least one item because dp[i][j-v] is not -1
                    if (~dp[i][j - v]) dp[i][j] = std::max(dp[i][j], dp[i][j - v] + w);
                    if (~dp[i - 1][j - v]) dp[i][j] = std::max(dp[i][j], dp[i - 1][j - v] + w);
                    // from groups[i - 1], ensure dp[i-1][j-v] has at least one item because dp[i-1][j-v] is not -1
                    // the order is not swap
                 }
                 */
            }
        }
    }
    return dp.back();
}
