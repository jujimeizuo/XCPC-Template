template <typename T>
std::vector<int> z_function(int n, const T &s) {
    std::vector<int> z(n, n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = (i > r ? 0 : std::min(r - i + 1, z[i - l]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
 
template <typename T>
std::vector<int> z_function(const T &s) {
    return z_function((int) s.size(), s);
}

template <typename T>
std::vector<int> z_search(int n, const T &s, int m, const T &w, std::vector<int> &z) {
    assert(n >= 1 && (int) z.size() == n);
    std::vector<int> p(m);
    int l = 0, r = -1;
    for (int i = 0; i < m; i++) {
        p[i] = (i > r ? 0 : std::min(r - i + 1, z[i - l]));
        while (i + p[i] < m && p[i] < n && s[p[i]] == w[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] - 1 > r) {
            l = i;
            r = i + p[i] - 1;
        }
    }
    return p;
};

template <typename T>
std::vector<int> z_search(const T &s, const T &w, std::vector<int> &z) {
    return z_search((int) s.size(), s, (int) w.size(), w, z);
};
