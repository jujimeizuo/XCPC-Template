const int N = 1e5 + 10;

int deg[N], toppar[N];
struct Edge {
    int u, v, next;
}e[N];

int head[N], cnt, tot;
int n, m;

inline void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
    deg[v]++;
}

void topsort() {
    queue<int> q;
    for(int i = 1;i <= n; i++) {
        if(deg[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int x = q.front(); q.pop();
        toppar[++tot] = x;
        for(int i = head[x]; i ; i = e[i].next) {
            int v = e[i].v;
            if(--deg[v] == 0) q.push(v);
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 1;i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    topsort();
    for(int i = 1;i <= tot; i++) cout << toppar[i] << endl;
}