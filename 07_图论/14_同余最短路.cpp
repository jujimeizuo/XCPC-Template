/*
洛谷P3403: 给定x[0], x[1], x[2], ..., x[n - 1], 对于k <= h, 求有多少个k满足a[0]x[0] + a[1]x[1] + ... + a[n - 1]x[n - 1] = k
洛谷P2662: 最大的不能被x[0], x[1], ..., x[n - 1]表示的数(从小到大), 显然如果gcd(x[i]) = x[0], 无解, 否则跑同余最短路求出max(dis) - x[0]即为答案
解决形如上述类型的题目
 */

/*
一是体现在建图
二是体现在最短路
*/

typedef long long ll;

const int N = 2e6 + 10;
#define INF 0x3f3f3f3f
struct Edge {
    int v, next;
    ll w;
}e[N];
int head[N], cnt;

void add(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

struct node {
    int now;
    ll d;
    bool operator < (const node& rhs) const {
        return d > rhs.d;
    }
};

priority_queue<node> q;
ll dis[N];

void Dij(int s, int n) {
    vector<bool> vis(n);
    for(int i = 0;i < n; i++) dis[i] = (INF);
    dis[s] = 1;
    q.push({s, 1});
    while(!q.empty()) {
        node p = q.top(); q.pop();
        int u = p.now;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            if(dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                q.push({v, dis[v]});
            }
        }
    }
}

ll solve(ll *x, int n, ll h) {
    sort(x, x + n);
    if(x[0] == 1) return h;
    for(int i = 0;i < x[0]; i++) {
        for(int j = 1;j < n; j++) {
            add(i, (i + x[j]) % x[0], x[j]);
        }
    }
    Dij(1, x[0]);
    ll ans = 0;
    for(int i = 0;i < x[0]; i++) {
        if(h >= dis[i]) ans += (h - dis[i]) / x[0] + 1;
    }
    return ans;
}

int main() {
    ll h, n; scanf("%lld", &h);
    for (int i = 0; i < n; i++) scanf("%lld", &x[i]);
    printf("%lld\n", solve(x, n, h));
}

/*----------------------------------------------------*/


const int N = 1e6 + 10;
struct edge {
    int v; ll w;
};

struct node {
    int now; ll d;
    bool operator < (const node& rhs) const {
        return d > rhs.d;
    }
};

vector<edge> g[5];
ll dis[5][N], w;

void Dij() {
    for(int i = 1;i <= 4; i++) {
        for(int j = 0;j < w; j++) {
            dis[i][j] = 1e18;
        }
    }
    dis[2][0] = 0;
    priority_queue<node> q;
    q.push({2, 0});
    while(!q.empty()) {
        node p = q.top(); q.pop();
        int u = p.now;
        if(dis[u][p.d % w] < p.d) continue;
        for(auto e : g[u]) {
            int v = e.v;
            ll len = e.w + p.d;
            if(dis[v][len % w] > len) {
                dis[v][len % w] = len;
                q.push({v, len});
            }
        }
    }
}

void solve() {
    int _; cin >> _;
    while(_--) {
        ll d12, d23, d34, d41, K;
        cin >> K >> d12 >> d23 >> d34 >> d41;
        g[1].emplace_back(edge{2, d12});g[2].emplace_back(edge{1, d12});
        g[2].emplace_back(edge{3, d23});g[3].emplace_back(edge{2, d23});
        g[3].emplace_back(edge{4, d34});g[4].emplace_back(edge{3, d34});
        g[4].emplace_back(edge{1, d41});g[1].emplace_back(edge{4, d41});
        w = 2 * min(d12, d23);
        Dij();
        ll ans = 1e19;
        for(int i = 0;i < w; i++) {
            if(dis[2][i] >= K) ans = min(dis[2][i], ans);
            else ans = min(ans, dis[2][i] + (K - dis[2][i] + w - 1) / w * w);
        }
        cout << ans << endl;
        for(int i = 1;i <= 4; i++) g[i].clear();
    }
}