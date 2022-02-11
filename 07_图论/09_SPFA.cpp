template<typename T>
class SPFA {
public :
    const int n;
    std::vector<std::vector<std::pair<int, T>>> edge;
    std::vector<bool> vis;
    std::vector<T> dis;
    std::vector<int> cnt;
    SPFA(int n) : n(n), edge(n), vis(n), dis(n, 1E9), cnt(n) {}

    void add(int u, int v, T w) {
        edge[u].emplace_back(make_pair(v, w));
    }
    bool spfa(int s) {
        queue<int> q;
        q.push(s);
        dis[s] = 0, vis[s] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = false;
            for(auto e : edge[u]) {
                if(dis[e.first] > dis[u] + e.second) {
                    dis[e.first] = dis[u] + e.second;
                    if(!vis[e.first]) {
                        cnt[e.first]++;
                        vis[e.first] = true;
                        if(cnt[e.first] >= n) return false;
                        q.push(e.first);
                    }
                }
            }
        }
        return true;
    }
};
