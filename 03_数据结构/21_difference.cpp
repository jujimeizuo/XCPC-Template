#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct difference {
    int n;
    std::vector<T> d;

    difference(int _n) : n(_n), d(_n + 1) {}
    difference(std::vector<T>& init) : difference(init.size()) {
        d[0] = init[0];
        for (int i = 1; i < n; i++) {
            d[i] = init[i] - init[i - 1];
        }
    }

    void modify(int l, int r, T v) {
        assert(0 <= l && l <= n - 1 && 0 <= r && r <= n - 1);
        d[l] += v;
        d[r + 1] -= v;
    }

    void solve() {
        for (int i = 1; i < n; i++) {
            d[i] += d[i - 1];
        }
    }
};

template <typename T>
struct difference2d {
    int n, m;
    std::vector<std::vector<T>> d;

    difference2d(int _n, int _m) : n(_n), m(_m), d(_n + 1, std::vector<T>(_m + 1)) {}
    difference2d(std::vector<std::vector<T>>& init) : difference2d(init.size(), init[0].size()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || j == 0) d[i][j] = init[i][j];
                else d[i][j] = init[i][j] - init[i - 1][j] - init[i][j - 1] + init[i - 1][j - 1];
            }
        }
    }

    void modify(int x1, int y1, int x2, int y2, T v) {
        assert(0 <= x1 <= n - 1 && 0 <= y1 <= n - 1 && 0 <= x2 <= n - 1 && 0 <= y2 <= n - 1);
        d[x1][y1] += v;
        d[x1][y2 + 1] -= v;
        d[x2 + 1][y1] -= v;
        d[x2 + 1][y2 + 1] += v;
    }
};