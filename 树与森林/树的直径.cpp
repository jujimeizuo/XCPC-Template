//树的直径性质：
//1、直径两端点一定是两个叶子节点
//2、距离任意点最远的点一定是直径的一个端点，这个基于贪心求直径方法的正确性可以得出
//3、对于两棵树，如果第一棵树直径两端点为(u,v)(u,v)，第二棵树直径两端点为(x,y)(x,y)，用一条边将两棵树连接，那么新树的直径一定是u,v,x,y,u,v,x,y,中的两个点
//4、对于一棵树，如果在一个点的上接一个叶子节点，那么最多会改变直径的一个端点
//5、若一棵树存在多条直径，那么这些直径交于一点且交点是这些直径的中点

const int N = 1e5 + 10;

// 两次DFS回朔法

struct Edge {
    int v, w, next;
}e[N * 2];

int cnt, head[N * 2];
int ans;
int D1, D2;
int Dis;

inline void add(int u, int v, int w) {
    e[++cnt].v = v;
    e[++cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

inline void DFS(int u, int fa, int t) {
    if(Dis < t) {
        D1 = u;
        Dis = t;
    }
    for(int i = head[u]; i ; i = e[i].next) {
        int v = e[i].v;
        if(v == fa) continue;
        DFS(v, u, t + e[i].w);
    }
}

void solve() {
    int n, M;
    cin >> n >> M;
    for(int i = 1;i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    Dis = 0; DFS(1, -1, 0);
    D2 = D1;
    Dis = 0; DFS(D1, -1, 0);
    cout << D1 << " " << D2 << endl;
    cout << Dis << endl;
}


const int N = 1e5 + 10;

struct Edge {
    int v, w;
};
vector<Edge> g[N];
int dp[N][2];
int ans;

void dfs(int u, int fa) {
    for(auto e : g[u]) {
        int v = e.v;
        if(v == fa) continue;
        dfs(v, u);
        if(dp[v][0] + e.w > dp[u][0]) {
            dp[u][1] = dp[u][0];
            dp[u][0] = dp[v][0] + e.w;
        }
        else if(dp[v][0] + e.w > dp[u][1]) dp[u][1] = dp[v][0] + e.w;
    }
    ans = max(ans, dp[u][0] + dp[u][1]);
}
