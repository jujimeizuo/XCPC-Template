// the numbers of exist 49 in 0~n
template <typename T>
T digitDP(T n) {
    T x = n;
    std::vector<int> digit;
    while (x) {
        digit.push_back(x % 10);
        x /= 10;
    }

    std::vector<std::vector<T>> dp(digit.size(), std::vector<T>(10));
    std::function<T(int, int, bool limit)> dfs = [&](int pos, int pre, bool limit) -> int {
        if (pos == -1) return 1;
        if (!limit && dp[pos][pre]) return dp[pos][pre];
        int up = limit ? digit[pos] : 9;
        T ans = 0;
        for (int i = 0; i <= up; i++) {
            if (pre == 4 && i == 9) {
                continue;
            }
            ans += dfs(pos - 1, i, limit && i == digit[pos]);
        }
        if (!limit) dp[pos][pre] = ans;
    };

    return dfs(digit.size() - 1, 0, 1);
}
