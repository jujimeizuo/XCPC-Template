// 一维排序、二维cdq、三维树状数组

const int N = 1e5 + 10;
struct node {
    int x, y, z;
    int id;
    int tag;
    bool operator < (const node &a)const{
        if(x != a.x) return x < a.x;
        if(y != a.y) return y < a.y;
        return z < a.z;
    }
    bool operator == (const node &a)const{
        return x == a.x && y == a.y && z == a.z;
    }
}a[N], b[N], tmp[N];

int ans[N];
int n;

void cdq2(int l, int r) {
    if(l == r) return ;
    int mid = (l + r) / 2;
    cdq2(l, mid); cdq2(mid + 1, r);
    int p = l, q = mid + 1, cnt = 0;
    for(int i = l;i <= r; i++) {
        if(q > r || (p <= mid && b[p].z <= b[q].z)) {
            if(b[p].tag == 0) cnt++;
            tmp[i] = b[p++];
        }
        else {
            if(b[q].tag == 1) ans[b[q].id] += cnt;
            tmp[i] = b[q++];
        }
    }
    for(int i = l;i <= r; i++) b[i] = tmp[i];
}

void cdq1(int l, int r) {
    if(l == r) return ;
    int mid = (l + r) / 2;
    cdq1(l, mid); cdq1(mid + 1, r);
    int p = l, q = mid + 1;
    /* 因为是计算左端元素对右端元素的影响，所以需要打个标记tag来记录他是左端还是右端元素 */
    for(int i = l;i <= r; i++) {
        if(q > r || (p <= mid && a[p].y <= a[q].y)) {
            a[p].tag = 0;
            b[i] = a[p++];
        }
        else {
            a[q].tag = 1;
            b[i] = a[q++];
        }
    }
    for(int i = l;i <= r; i++) a[i] = b[i];
    cdq2(l, r);
}

void solve() {
    n = read();
    for(int i = 1;i <= n; i++) {
        a[i].x = read(), a[i].y = read(), a[i].z = read();
        a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    for(int i = n - 1;i >= 1; i--) {
        if(a[i + 1] == a[i]) ans[a[i].id] = ans[a[i + 1].id] + 1;
    }
    cdq1(1, n);
    for(int i = 1;i <= n; i++) cout << ans[i] << endl;
}