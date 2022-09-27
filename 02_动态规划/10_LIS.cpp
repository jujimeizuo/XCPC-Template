template <typename T>
int lis(const std::vector<T>& a) {
    std::vector<T> u;
    for (const T& x : a) {
        auto it = upper_bound(u.begin(), u.end(), x);
        if (it == u.end()) {
            u.push_back(x);
        } else {
            *it = x;
        }
    }
    return (int) u.size();
}
