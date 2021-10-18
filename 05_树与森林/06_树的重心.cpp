const int N = 1e5 + 10;

struct Edge {
    int v, next;
}e[N * 2];

int cnt, head[N * 2];

int d[N], R[2], root;
int n;

int balance;

inline void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

void DFS(int u, int fa) {
    d[u] = 1;
    int res = 0;
    for(int i = head[u] ; i != -1 ; i = e[i].next) {
        int v = e[i].v;
        if(v == fa) continue;
        DFS(v, u);
        d[u] += d[v];
        res = max(res, d[v]);
    }
    res = max(res, n - d[u]);
    if(res < balance) {
        R[root++] = u;
        balance = res;
    }
    else if(res == balance) {
        R[root++] = u;
    }
}

int main() {
    cin >> n;
    balance = n / 2;
    for(int i = 1;i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    DFS(1, 0);
    if(R[0]) cout << R[0] << endl;
    if(R[1]) cout << R[1] << endl;
}