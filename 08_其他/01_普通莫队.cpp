// O(n*sqrt(n))
const int N = 1e5 + 10;

int a[N], cnt[N], ans[N];
int belong[N];

struct Q {
    int l, r, id;
}q[N];

int Size, bnum;

bool cmp(Q a, Q b) {
    return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : belong[a.l] & 1 ? a.r < b.r : a.r > b.r; 
}

int now = 0;

inline void add(int pos) {
    if(!cnt[a[pos]]) now++;
    ++cnt[a[pos]];
}

inline void del(int pos) {
    --cnt[a[pos]];
    if(!cnt[a[pos]]) --now;
}

int main() {
    int n, m;
    cin >> n >> m;
    Size = sqrt(n);
    bnum = ceil((double)n / Size);
    for(int i = 1;i <= bnum; i++) {
        for(int j = (i - 1) * Size + 1;j <= i * Size; j++) {
            belong[j] = i;
        }
    }
    for(int i = 1;i <= n; i++) cin >> a[i];
    for(int i = 1;i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q + 1, q + m + 1, cmp);
    int l = 1, r = 0;
    for(int i = 1;i <= m; i++) {
        int ql = q[i].l, qr = q[i].r;
        while(r < qr) add(++r);
        while(r > qr) del(r--);
        while(l < ql) del(l++);
        while(l > ql) add(--l);
        ans[q[i].id] = now;
    }
    for(int i = 1;i <= m; i++) cout << ans[i] << endl;  
}

