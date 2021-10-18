const int N = 2e5 + 10;

vector<int> g[N];

int siz[N], son[N], col[N];
int ans[N], cnt[N];
bool vis[N];
int maxx, sum;
// maxx为每棵子树里出现最多的颜色，sum为编号和

void calc(int u, int fa, int val) {
    /*
    针对不同问题，采取的操作
    */
    else if(val > 0 && cnt[col[u]] == maxx) sum += col[u];
    for(auto v : g[u]) {
        if(v != fa && !vis[v]) calc(v, u, w);
    }
}

void dfs1(int u, int fa) {
    siz[u] = 1;
    for(auto v : g[u]) {
        if(v == fa) continue ;
        dfs1(v, u);
        siz[u] += siz[v];
        if(!son[u] || siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fa, bool keep) {
    for(auto v : g[u]) {
        if(v != fa && v != son[u]) {
            dfs2(v, u, 0);
        }
    }
    if(son[u]) {
        dfs2(son[u], u, 1);
        vis[son[u]] = 1;
    }
    calc(u, fa, 1);
    ans[u] = sum;
    if(son[u]) vis[son[u]] = 0;
    if(!keep) {
        calc(u, fa, -1);
        maxx = sum = 0;
    }
}

int main() {
    int n; cin >> n;
    for(int i = 1;i <= n; i++) cin >> col[i];
    for(int i = 1;i < n; i++) {
        int u,  v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs0(1, 0);
    dfs1(1, 0, false);
    for(int i = 1;i <= n; i++) cout << ans[i] << endl;
}