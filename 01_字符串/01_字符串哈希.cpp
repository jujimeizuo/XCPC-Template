// 区间哈希

const int N = 100010, P = 131;  // 这里的P 是经验值 131 ，或者13331

int n,m;
char str[N];
// 这里用unsigned long long 存储就相当于mod 2 ^ 64, 因为超过了会溢出的
ULL h[N], p[N];   // h[]是存储字符串哈希值的  p[] 是存储p次方的  

ULL get(int l, int r) {
    return h[r] - h[l -1] * p[r - l + 1];     // 区间hash 的公式
}

int main() {
    scanf("%d%d%s", &n, &m, str + 1);

    p[0] = 1;
    for(int i=1; i<=n; i++) {
        p[i] = p[i-1] * P;  // p数组保存 计算的次方数
        h[i] = h[i-1] * P +str[i];   // 计算字符串的前缀，  后面的是0次 所以直接加上str[i]就行了
    }

    while(m -- ) {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2)   ;
        if(get(l1, r1) == get(l2, r2)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

// 线段树维护区间哈希
struct Tree {
    int l, r;
    ull sum;
    Tree operator + (const Tree &a) const {
        Tree ans;
        ans.l = l, ans.r = a.r;
        ans.sum = sum * p[a.r - a.l + 1] + a.sum;
        return ans;
    }
}t[N << 2];
