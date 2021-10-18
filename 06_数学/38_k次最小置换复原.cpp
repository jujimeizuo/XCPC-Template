
void solve() {
    int n; cin >> n;
    vector<int> a(n + 1), vis(n + 1);
    for(int i = 1;i <= n; i++) cin >> a[i];
    ll ans = 1;
    for(int i = 1;i <= n; i++) {
        if(!vis[i]) {
            int cnt = 0;
            int x = i;
            while(!vis[x]) {
                vis[x] = 1;
                cnt++;
                x = a[x];
            }
            ans = lcm(ans, cnt);
        }
    }
    cout << ans << endl;
}

