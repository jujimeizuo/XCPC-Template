template<typename T>
class Kruskal {
public :
    const int n;
    T ans;
    std::vector<tuple<int, int, T>> edge;
    Kruskal(int n) : n(n), edge(n), ans(0) {}
    void add(int u, int v, T w) {
        edge.emplace_back(u, v, w);
    }
    void kruskal() {
        int cnt = 0;
        DSU g(n);
        sort(edge.begin(), edge.end(), [&](tuple<int, int, T> a, tuple<int, int, T> b) {
            return get<2>(a) < get<2>(b);
        });
        for(auto e : edge) {
            int u, v; T w;
            tie(u, v, w) = e;
            if(!g.merge(u, v)) continue ;
            ans += w;
            if(++cnt == n - 1) break ;
        }
    }
};
