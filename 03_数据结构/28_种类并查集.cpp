// 根据题目要求，若是集合中有n个关系，那需要开n倍的并查集大小

const int N = 1e5 + 10;
int f[N * 2], dep[N * 2];

int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return ;
    if(dep[x] <= dep[y]) {
        f[x] = y; dep[y] = max(dep[x] + 1, dep[y]);
    }
    else { 
        f[y] = x; dep[x] = max(dep[y] + 1, dep[x]);
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1;i <= 2 * n; i++) f[i] = i;// **

    while(q--) {
        int flag, x, y;
        cin >> flag >> x >> y;
        if(flag) { // 敌人
            merge(x + n, y);
            merge(y + n, x);
        }
        else {
            merge(x, y); // 同伴
        }
    }    
    int ans = 0;
    for(int i = 1;i <= n; i++) {
        if(f[i] == i) ans ++;
    }
    cout << ans << endl;
}
