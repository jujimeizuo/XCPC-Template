template <typename T>
T binaryMultipleKnapSack(const std::vector<int>& v, const std::vector<T>& w, const std::vector<int>& cnt, int V) {
    int n = (int) v.size();
    std::vector<T> dp(V + 1);
    std::vector<std::array<T, 2>> bags;
    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= cnt[i]; k <<= 1) {
            cnt[i] -= k;
            bags.push_back({v[i] * k, w[i] * k});
        }
        if (cnt[i] > 0) {
            bags.push_back({v[i] * cnt[i], w[i] * cnt[i]});
        }
    }
    for (auto& [nv, nw] : bags) {
        for (int j = V; j >= nv; j--) {
            dp[j] = std::max(dp[j], dp[j - nv] + nw);
        }
    }
    return dp.back();
}