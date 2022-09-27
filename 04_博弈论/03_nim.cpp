template <typename T>
bool nimGame(const std::vector<T>& stones) {
    int res = 0;
    for (int &x : stones) {
        res ^= x;
    }
    return res;
}