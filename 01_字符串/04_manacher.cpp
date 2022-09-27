template <typename T>
std::vector<int> manacher(int n, const T &s) {
    if (n == 0) {
        return std::vector<int>();
    }
    std::vector<int> res(2 * n - 1, 0);
    int l = -1, r = -1;
    for (int z = 0; z < 2 * n - 1; z++) {
        int i = (z + 1) >> 1;
        int j = z >> 1;
        int p = (i >= r ? 0 : std::min(r - i, res[2 * (l + r) - z]));
        while (j + p + 1 < n && i - p - 1 >= 0) {
            if (!(s[j + p + 1] == s[i - p - 1])) {
                break;
            }
            p++;
        }
        if (j + p > r) {
            l = i - p;
            r = j + p;
        }
        res[z] = p;
    }
    return res;
}
 
template <typename T>
std::vector<int> manacher(const T &s) {
    return manacher((int) s.size(), s);
}
