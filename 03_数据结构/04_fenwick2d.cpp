template <typename T>
class Fenwick2d {
public:
    std::vector<std::vector<T>> fenw;
    const int n, m;

    Fenwick2d(int _n, int _m) : n(_n), m(_m) {
        fenw.resize(n);
        for (int i = 0; i < n; i++) {
            fenw[i].resize(m);
        }
    }

    inline void modify(int i, int j, T v) {
        int x = i;
        while (x < n) {
            int y = j;
            while (y < m) {
                fenw[x][y] += v;
                y |= (y + 1);
            }
            x |= (x + 1);
        }
    }

    inline T get(int i, int j) {
        T v{};
        int x = i;
        while (x >= 0) {
            int y = j;
            while (y >= 0) {
                v += fenw[x][y];
                y = (y & (y + 1)) - 1;
            }
            x = (x & (x + 1)) - 1;
        }
        return v;
    }
};