// 求二维平面上(x1,y1)到(x2,y2)的矩阵中数点

// 利用前缀和思想，把问题划分成[x2,y2] - [x1-1,y2] - [x2,y2-1] + [x1-1,y1-1]

// 所有要建立4个虚点为查询点，而原本实点为修改点

const int N = 3e6 + 10;

struct node {
    int x, y, opt, id;
    // opt为操作类型，1为修改，0为查询
    bool operator < (const node& o) const {
        return x == o.x ? (y == o.y ? opt : y < o.y) : x < o.x;
    }
    // 注意排序顺序，坐标相同时，要使opt放前面，因为要先修改

    bool operator == (const node &o) const {
        return x == o.x && y == o.y;
    }
}a[N], tmp[N];

int ans[N];

void cdq(int l, int r) {
    if(l == r) return ;
    int mid = (l + r) / 2;
    cdq(l, mid); cdq(mid + 1, r);
    int p = l, q = mid + 1, cnt = 0;
    for(int i = l;i <= r; i++) {
        if(q > r || (p <= mid && a[p].y <= a[q].y)) {
            cnt += a[p].opt;
            tmp[i] = a[p++];
        }
        else {
            ans[a[q].id] += cnt;
            tmp[i] = a[q++];
        }
    }
    for(int i = l;i <= r; i++) a[i] = tmp[i];
}

void solve() {
    int n = read(), m = read();
    for(int i = 1;i <= n; i++) {
        a[i].x = read(), a[i].y = read(), a[i].opt = 1;
    }
    int _n = 0;
    for(int i = 1;i <= m; i++) {
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        a[++n] = (node){x2, y2, 0, ++_n};
        a[++n] = (node){x2, y1 - 1, 0, ++_n};
        a[++n] = (node){x1 - 1, y2, 0, ++_n};
        a[++n] = (node){x1 - 1, y1 - 1, 0, ++_n};
    }
    sort(a + 1, a + n + 1);
    cdq(1, n);
    for(int i = 1;i + 3 <= _n; i += 4) {
        cout << ans[i] - ans[i + 1] - ans[i + 2] + ans[i + 3] << endl;
    }
}
