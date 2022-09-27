#include "bits/stdc++.h"
using namespace std;
//A*
//用来计算点A到点B的第k短的路径

const int MAXN = 55;
const int MAXM = MAXN * MAXN;

int dis[MAXN];
int n, m, k, a, b, cnt;
bool hav = false;

namespace G1{//反图
    int to[MAXM], val[MAXM], head[MAXN], nxt[MAXM], cnt;
    bool vis[MAXN];

    void AddEdge(int u, int v, int w) {
        cnt++;
        to[cnt] = v;
        val[cnt] = w;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    void Spfa(int s, int t) {//SPFA+SLF跑最短路
        memset(dis, 0x7f, sizeof(dis)); dis[s] = 0;
        deque<int> q; q.push_back(s); vis[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop_front(); vis[u] = false;
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (dis[v] > dis[u] + val[i]) {
                    dis[v] = dis[u] + val[i];
                    if (!vis[v]) {
                        vis[v] = true;
                        if (!q.empty() && dis[v] < dis[q.front()]) {
                            q.push_front(v);
                        } else {
                            q.push_back(v);
                        }
                    }
                }
            }
        }
    }
}

namespace G2{//原图
    int to[MAXM], val[MAXM], nxt[MAXM], head[MAXN], cnt;

    void AddEdge(int u, int v, int w) {
        cnt++;
        to[cnt] = v;
        val[cnt] = w;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    struct Data{//当前位置，走过的距离，s->now->t总距离，走的步骤
        int now, pas, val;
        vector<int> route;
        /*
        bool operator < (const Data &b) const {return val > b.val;}
        */
        bool operator < (const Data &b) const {//重载
            if (val != b.val) return val > b.val;
            int sz = min(route.size(), b.route.size());
            for (int i = 0; i < sz; i++) {
                if (route[i] != b.route[i]) return route[i] > b.route[i];
            }
            return route.size() > b.route.size();
        }
    };

    void Astar(int s, int t) {//A*
        priority_queue<Data> q;
        Data st;
        st.now = s; st.pas = 0; st.val = dis[s]; st.route = vector<int>{s};
        q.push(st);
        vector<int> vec;
        while (!q.empty()) {
            Data u = q.top(); q.pop();
            if (u.now == t) {//更新路径数
                :: cnt++;
                if (:: cnt == k) {//最终答案
                    cout << u.route[0];
                    for (int i = 1, sz = u.route.size(); i < sz; i++)
                        cout << '-' << u.route[i];
                    hav = true;
                    return;
                }
            }
            for (int i = head[u.now]; i; i = nxt[i]) {//广搜
                int v = to[i];
                vec = u.route;
                bool visit = false;
                for (int j = 0, sz = vec.size(); j < sz; j++) {//记录是否重复经过
                    if (vec[j] == v) {
                        visit = true;
                        break;
                    }
                }
                if (visit) continue;
                Data nx = u;
                nx.now = v;
                nx.pas = u.pas + val[i];
                nx.val = dis[v] + nx.pas;
                nx.route.push_back(v);
                q.push(nx);
            }
        }
    }
}

int main() {
    cin >> n >> m >> k >> a >> b;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G1 :: AddEdge(v, u, w);
        G2 :: AddEdge(u, v, w);
    }
    G1 :: Spfa(b, a);
    G2 :: Astar(a, b);
    if (!hav) cout << "No" << endl;
    return 0;
}