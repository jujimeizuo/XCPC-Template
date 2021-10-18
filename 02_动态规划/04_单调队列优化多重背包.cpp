const int N = 1e5 + 10;

int que[N], head, tail;
int f[N], pre[N];
void solve() {
    int n, m; cin >> n >> m;
    for(int i = 1;i <= n; i++) {
        memcpy(pre, f, sizeof(f));
        int v, w, s; cin >> v >> w >> s;
        for(int j = 0;j < v; j++) {
            head = 1; tail = 0;
            for(int k = j;k <= m; k += v) {
                while(head <= tail && que[head] < k - s * v) head++;
                if(head <= tail) f[k] = max(pre[k], pre[que[head]] + (k - que[head]) / v * w);
                while(head <= tail && pre[k] >= pre[que[tail]] + (k - que[head]) / v * w) tail--;
                que[++tail] = k;
            }
        }
    }
    cout << f[m] << endl;
}
