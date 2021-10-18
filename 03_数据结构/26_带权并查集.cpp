// 根据题目时候并成链还是树
const int N = 1e5 + 10;
int d[N], f[N];

int find(int x) {
    if(f[x] != x) {
        int fa = f[x];
        f[x] = find(f[x]);
        d[x] += d[fa];
    }
    return f[x];
}

void merge(int x, int y, int v) { // 两个点和权值
    int px = find(x);
    int py = find(y);
    if(px == py) return ;
    else {
        f[px] = py;
        d[px] = d[y] + v - d[x];
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n; i++) f[i] = i;
    while(m--) {
        int x, y, v;
        cin >> x >> y >> v;
        merge(x, y, v);
    }
}
