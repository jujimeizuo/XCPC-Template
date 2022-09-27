template <typename T>
T hybridKnapSack(const std::vector<int>& v, const std::vector<T>& w, const std::vector<int>& cnt, int V) {
    int n = (int) v.size();
    std::vector<T> dp(V + 1);
    std::vector<std::tuple<int, T, int> > bags;
    for (int i = 0; i < n; i++) {
        if (cnt[i] < 0) {
            bags.push_back(std::make_tuple(v[i], w[i], -1));
        } else if (cnt[i] == 0) {
            bags.push_back(std::make_tuple(v[i], w[i], 0));
        } else {
            for (int k = 1; k <= cnt[i]; k <<= 1) {
                cnt[i] -= k;
                bags.push_back(std::make_tuple(v[i] * k, w[i] * k, -1));
            }
            if (cnt[i] > 0) {
                bags.push_back(std::make_tuple(v[i] * cnt[i], w[i] * cnt[i], -1));
            }
        }
    }
    for (auto& bag : bags) {
        int v, w, op;
        std::tie(v, w, op) = bag;
        if (op == -1) {
            for (int j = V; j >= v; j--) {
                dp[j] = std::max(dp[j], dp[j - v] + w);
            }
        } else {
            for (int j = v; j <= V; j++) {
                dp[j] = std::max(dp[j], dp[j - v] + w);
            }
        }
    }
    return dp.back();
}