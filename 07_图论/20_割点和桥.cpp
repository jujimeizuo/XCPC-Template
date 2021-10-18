const int N = 2e5 + 10;

struct Edge{
    int u, v, next;
}e[N * 2];

int head[N], cnt;

int dfn[N], low[N]; // 第一次访问到的节点的编号和最早访问的节点的编号（时间戳）
bool vis[N]; // 标记节点是否访问过并且还在栈中
int fa[N]; // 父亲节点
int Time = 1;
set<int> s1;
set<pair<int, int> > s2;

void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

void DFS(int u) {
    dfn[u] = low[u] = Time++;
    int child = 0;

    for(int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;

        if(!dfn[v]) {
            child++;
            fa[v] = u;
            DFS(v);
            if(fa[u] == -1 && child >= 2) // u是根节点，并且有两个儿子----是割点
                s1.insert(u);
            else if(fa[u] != -1 && low[v] >= dfn[u]) // u不是根节点，并且有儿子，并且low[v]>=low[u]----是割点
                s1.insert(u);
            else if(low[v] > dfn[u])
                s2.insert({u, v});
            low[u] = min(low[u], low[v]);
        }
        else if(v != fa[u]) // 这一步说明可以不经过父亲而回到祖先，可以尝试更新(条件可以不写，不影响)
            low[u] = min(low[u], dfn[v]);
    }
}

void Tarjan() {
    int n, m;
    cin >> n >> m;
    memset(fa, -1, sizeof(fa));

    for(int i = 1;i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    
    for(int i = 1;i <= n; i++) {
        if(!dfn[i])
            DFS(i);
    }

    cout << s1.size() << endl;
    for(auto x : s1) cout << x << endl;

    cout << s2.size() << endl;
    for(auto x : s2) cout << x.first << "---" << x.second << endl;
}

