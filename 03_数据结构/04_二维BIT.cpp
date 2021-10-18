
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int t[N][N];
int n;

int lowbit(int x) {
    return x & (-x);
}

void update(int x, int y, int val) {
    for(int i = x;i > 0; i -= lowbit(x)) {
        for(int j = y;j > 0; y -= lowbit(y)) {
            t[i][j] += val;
        }
    }
}

int query(int x, int y) {
    int res = 0;
    for(int i = x;i <= n; i += lowbit(x)) {
        for(int j = y;j <= n; j += lowbit(y)) {
            res += t[i][j];
        }
    }
    return res;
}

int main() {
    int m;
    cin >> n >> m;
    while(m--) {
        int opt;
        cin >> opt;
        if(opt == 1) {
            int x1, y1, x2, y2, val;
            cin >> x1 >> y1 >> x2 >> y2 >> val;
            update(x2, y2, val);
            update(x1 - 1, y2, -val);
            update(x2, y1 - 1, -val);
            update(x1 - 1, y1 - 1, val);
        }
        else {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << endl;
        }
    }
}