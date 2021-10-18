// 树状数组和二进制紧紧联系

int tree[100005];
int n;

int lowbit(int x) {
    return x & (-x); // 计算机中负数使用对应正数的补码表示
}

int getsum(int x) {
    int ans = 0;
    while(x > 0) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

void update(int x,int value) {
    while(x <= n) {
        tree[x] += value;
        x += lowbit(x);
    }
}

/*-------区间最大值--------*/
int t[N], a[N];
void modify(int x) {
    while(x <= n) {
        t[x] = a[x];
        for(int i = 1;i < lowbit(x); i <<= 1) {
            t[x] = max(t[x], t[x - i]);
        }
        x += lowbit(x);
    }
}

int query(int l, int r) {
    int ans = 0;
    while(l <= r) {
        ans = max(ans, a[r]);
        for (r-- ;r - lowbit(r) >= l; r -= lowbit(r)) {
            ans = max(ans, t[r]);
        }
    }
    return ans;
}