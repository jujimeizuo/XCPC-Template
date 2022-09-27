class Fib {
    int n;
    std::vector<std::vector<int>> f;
    Fib(int _n) : n(_n), f(_n, std::vector<int>(_n)) {
        f[1][1] = 1;
        f[2][1] = 1;
        int s, add = 0;
        for (int i = 3; i < _n; i++) {
            for (int j = 1; j < _n; j++) {
                s = f[i - 2][j] + f[i - 1][j] + add;
                f[i][j] = s % 10;
                add = s / 10;
            }
        }
    }

    std::string get(const int m) {
        int k = n - 1;
        while (!f[m][k]) k--;
        std::string s = "";
        s.push_back(f[n][k] + '0');
        return s;
    }
};