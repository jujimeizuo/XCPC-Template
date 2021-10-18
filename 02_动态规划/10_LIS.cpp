typedef long long ll;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int a[N], f[N];

int n;
int ans;

int DP() {
    for(int i = 1;i <= n; i++) {
        f[i] = 1;
    }
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j < i; j++) {
            if(a[j] < a[i]) 
                f[i] = max(f[i], f[j] + 1);
        }
    }
    for(int i = 1;i <= n; i++) {
        ans = max(ans, f[i]);
    }
    return ans;
}

int stl() {
    int d[N];
    fill(f, f + n, INF);
    for(int i = 0;i < n; i++) {
        int j = lower_bound(f, f + n, a[i]) - f;
        d[i] = j + 1;
        if(ans < d[i]) {
            ans = d[i];
        }
        f[j] = a[i];
    }
    return ans;
}

int t[N];
int maxn;

int lowbit(int x) {
    return x & (-x);
}

void update(int k, int val) {
    while(k <= maxn) {
        t[k] = max(t[k], val);
        k += lowbit(k);
    }
}

int query(int k) {
    int res = 0;
    while(k) {
        res = max(res, t[k]);
        k -= lowbit(k);
    }
    return res;
}

int Tree() {
    for(int i = 1;i <= n; i++) {
        maxn = max(maxn, a[i]);
    }

    int ans = 0;
    for(int i = 1;i <= n; i++) {
        int q = query(a[i]) + 1; // 保证j < i，找f[j]最大的
        update(a[i], q);
        ans = max(ans, q);
    }
    return ans;
}


