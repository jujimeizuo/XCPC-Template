// 一维排序、二维cdq、三维树状数组

const int N = 1e5 + 10;
struct node {
    int x, y, z;
    int id;
    bool operator < (const node &a)const{
        if(x != a.x) return x < a.x;
        if(y != a.y) return y < a.y;
        return z < a.z;
    }
    bool operator == (const node &a)const{
        return x == a.x && y == a.y && z == a.z;
    }
}a[N], b[N];
int n;


int ans[N];

struct BIT {
#define lowbit(x) (x & (-x))
    int n;
    int t[N];

    void init(int _n) {
        mem(t, 0);
        n = _n;
    }

    void update(int x, int val) {
        while (x <= n) {
            t[x] += val;
            x += lowbit(x);
        }
    }

    int query(int x) {
        int ans = 0;
        while (x) {
            ans += t[x];
            x -= lowbit(x);
        }
        return ans;
    }
}bit;

void cdq(int l, int r) {
    if(l == r) return ;
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    int p = l, q = mid + 1;
    for(int i = l;i <= r; i++) {
        if(q > r || (p <= mid && a[p].y <= a[q].y)) {
            bit.update(a[p].z, 1);
            b[i] = a[p++];
        }
        else {
            ans[a[q].id] += bit.query(a[q].z);
            b[i] = a[q++];
        }
    }
    for(int i = l;i <= mid; i++) bit.update(a[i].z, -1);
    for(int i = l;i <= r; i++) a[i] = b[i];
}

void solve() {
    n = read();
    int mx = 0;
    for(int i = 1;i <= n; i++) {
        a[i].x = read(), a[i].y = read(), a[i].z = read();
        a[i].id = i;
        mx = max(mx, a[i].z);
    }
    bit.init(mx);
    sort(a + 1, a + n + 1);
    for(int i = n - 1;i >= 1; i--) {
        if(a[i] == a[i + 1]) ans[a[i].id] = ans[a[i + 1].id] + 1;
    }
    cdq(1, n);
    for(int i = 1;i <= n; i++) cout << ans[i] << endl;
}
