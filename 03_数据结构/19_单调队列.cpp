const int N = 2e5 + 10;
int f[N], que[N], tail, head;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1;i <= n; i++) cin >> a[i];
    // 维护最小值
    tail = 1; head = 0;
    for(int i = 1;i <= n; i++) {
        while(tail >= head && f[tail] >= a[i]) tail--;
        que[++tail] = i;
        f[tail] = a[i];
        while(que[head] + k <= i) head++;
        if(i >= k) cout << f[head] << " ";
    }
    cout << endl;
    
    // 维护最大值
    tail = 1; head = 0;
    for(int i = 1;i <= n; i++) {
        while(tail >= head && f[tail] <= a[i]) tail--;
        que[++tail] = i;
        f[tail] = a[i];
        while(que[head] + k <= i) head++;
        if(i >= k) cout << f[head] << " ";
    }
    cout << endl;
}