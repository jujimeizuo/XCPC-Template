// no correct
template <typename T>
T monotonousQueueMultipleKnapSack(const std::vector<int>& v, const std::vector<T>& w, const std::vector<int>& cnt, int V) {
    int n = (int) v.size();
    std::vector<T> dp(V + 1);
    std::vector<int> que(V);
    for (int i = 0; i < n; i++) {
        std::vector<T> ndp(V + 1);
        for (int j = 0; j < v[i]; j++) {
            int head = 1, tail = 0;
            for (int k = j; k <= V; k += v[i]) {
                while (head <= tail && que[head] < k - cnt[i] * v[i]) head++;
                if (head <= tail) ndp[k] = std::max(dp[k], dp[que[head]] + (k - que[head]) / v[i] * w[i]);
                while (head <= tail && dp[k] >= dp[que[tail]] + (k - que[head]) / v[i] * w[i]) tail--;
                que[++tail] = k;
            }
        }
        dp = std::move(ndp);
    }
    return dp.back();
}
