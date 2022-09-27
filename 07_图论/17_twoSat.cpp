class twosat {
public:
    digraph<int> g;
    int n;
 
    twosat(int _n) : g(digraph<int>(2 * _n)), n(_n) {}
 
    inline void add(int x, int value_x) {
        assert(0 <= x && x < n);
        assert(0 <= value_x && value_x <= 1);
        g.add(2 * x + (value_x ^ 1), 2 * x + value_x);
    }
  
    inline void add(int x, int value_x, int y, int value_y) {
        assert(0 <= x && x < n && 0 <= y && y < n);
        assert(0 <= value_x && value_x <= 1 && 0 <= value_y && value_y <= 1);
        g.add(2 * x + (value_x ^ 1), 2 * y + value_y);
        g.add(2 * y + (value_y ^ 1), 2 * x + value_x);
    }
 
    inline std::vector<int> solve() {
        int cnt;
        std::vector<int> c = find_scc(g, cnt);
        std::vector<int> res(n);
        for (int i = 0; i < n; i++) {
            if (c[2 * i] == c[2 * i + 1]) {
                return std::vector<int>();
            }
            res[i] = (c[2 * i] < c[2 * i + 1]);
        }
        return res;
    }
};