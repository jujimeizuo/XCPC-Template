template<typename T>
class Prim {
    const int n;
    T ans;
    std::vector<std::vector<std::pair<int, T>>> edge;
    std::vector<bool> vis;
    std::vector<T> dis;
    struct node {
       int now;
       T d;
       bool operator < (const node& rhs) const {
           return d > rhs.d;
       }
    };
    Prim(int n) : ans(0), n(n), edge(n), vis(n), dis(n, 1E9) {}

    void add(int u, int v, T w) {
        edge[u].emplace_back(make_pair(v, w));
    }
    void prim() {
        priority_queue<node> q; q.push({0, 0});
        int cnt = 0;
        while(!q.empty() && cnt <= n) {
            node p = q.top(); q.pop();
            int u = p.now;
            T dis = p.d;
            if(vis[u]) continue ;
            vis[u] = true, cnt++, ans += dis;
            for(auto e : edge[u]) {
                if(!vis[e.first]) q.push({e.first, e.second});
            }
        }
    }
};
