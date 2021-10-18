
const int N = 1e5 + 10;
int ans[N], cnt[N];

struct star {
    int x, y, id;
}a[N], tmp[N];

bool cmp(star a, star b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

void cdq(int l, int r) {
    if(l == r) return ;
    int m = (l + r) / 2;
    cdq(l, m);
    cdq(m + 1, r);
    int p = l, q = m + 1;
    for(int i = l;i <= r; i++) {
        if((p <= m && a[p].x <= a[q].x) || q > r) {
            tmp[i] = a[p++]; 
        }
        else {
            ans[a[q].id] += i - l;
            tmp[i] = a[q++];
        }
    }
    for(int i = l;i <= r; i++) a[i] = tmp[i];
}

void solve() {
    int n; cin >> n;
    for(int i = 1;i <= n; i++) cin >> a[i].x >> a[i].y;
    sort(a + 1, a + n + 1, cmp);
    cdq(1, n);
    for(int i = 1;i <= n; i++) cnt[ans[i]]++;
    for(int i = 0;i < n; i++) cout << cnt[i] << endl;
}