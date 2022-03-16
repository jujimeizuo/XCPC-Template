template<typename T>
class Dijkstra {
public :
    const int n;
    std::vector<std::vector<std::pair<int, T>>> edge;
    std::vector<T> dis;
    std::vector<bool> vis;

    struct node {
        int now; T d;
        bool operator < (const node &rhs) const {
            return d > rhs.d;
        }
    };

    Dijkstra(int n) : n(n), edge(n), vis(n), dis(n, 1E9) {}
    void add(int u, int v, T w) {
        edge[u].emplace_back(make_pair(v, w));
    }
    void Dij(int s) {
        priority_queue<node> q;
        dis[s] = 0;
        q.push({s, 0});
        while(!q.empty()) {
            node p = q.top();
            q.pop();
            int u = p.now;
            if(vis[u]) continue;
            vis[u] = 1;
            for(auto e : edge[u]) {
                if(dis[e.first] > dis[u] + e.second) {
                    dis[e.first] = dis[u] + e.second;
                    q.push({e.first, dis[e.first]});
                }
            }
        }
    }
};
