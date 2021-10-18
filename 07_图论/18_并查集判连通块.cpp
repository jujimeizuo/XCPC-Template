const int maxn = 5e5 + 10;

int n, m, k;
int pre[maxn], cnt[maxn];

int find(int x) {
    if(pre[x] == x)
        return x;
    int y = find(pre[x]);
    pre[x] = y;
    return y;
}

void merge(int u, int v) {
    int x = find(u);
    int y = find(v);
    if(x != y) pre[x] = y;
}

void init(int n) {
    for(int i = 1;i <= n; i++) {
        pre[i] = i;
        cnt[i] = 0;
    }
}

void solve() {
    cin >> n >> m;
    init(n);
    int u, v;
    for(int i = 1;i <= m; i++) {
        cin >> u >> v;
        merge(u, v);
    }
    
    int ans = 0;
    // first
    for(int i = 1;i <= n; i++) {
        cnt[find(i)]++;
    }
    for(int i = 1;i <= n; i++) {
        if(cnt[i])
            ans++;
    }
    
    //second
    for(int i = 1;i <= n; i++) {
        int s = find(i);
        if(cnt[s] == 0) {
            cnt[s]++;
            ans++;
        }
    }
    
    //third
    for(int i = 1;i <= n; i++) {
        if(pre[i] == i)
            ans++;
    }
    cout << ans << endl;
}