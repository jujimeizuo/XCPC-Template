struct Hash {
using ui64 = unsigned long long;
    static constexpr int P = 1331;
    std::vector<ui64> h, p;

    Hash(std::string s) : h(s.size() + 1), p(s.size() + 1) {
        p[0] = 1;
        for (int i = 1;i <= (int) s.size(); i++) {
            p[i] = p[i - 1] * P;
            h[i] = h[i - 1] * P + s[i - 1] - '0';
        }
    }

    ui64 rangeSum(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
};
