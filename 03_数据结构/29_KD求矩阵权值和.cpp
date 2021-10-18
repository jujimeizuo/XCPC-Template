#include <bits/stdc++.h>
using namespace std;

const int MAX = 200005;
const double alpha = 0.75;
//查包含在x1,y1,x2,y2为左下角和右上角的矩形里面权值之和
//K-D Tree 二维划分树
int n, ans, rt, WD, tot, top, rub[MAX];

struct node {
    int x[2], w;
} p[MAX];

struct K_D_tree {
    int ls, rs, siz, mn[2], mx[2], sum;
    //mn[0], mx[0] -> x的取值范围
    //mn[1], mx[1] -> y的取值范围
    node tmp;
} t[MAX];

int operator < (const node &a, const node &b) { return a.x[WD] < b.x[WD]; }

int newnode() {
    if (top) return rub[top--];
    else return ++tot;
}

void push_up(int u) {
    for (int i = 0; i <= 1; i++) {//更新x, y的取值范围
        t[u].mn[i] = t[u].mx[i] = t[u].tmp.x[i];
        if (t[u].ls) {//左子树的最大最小值
            t[u].mn[i] = min(t[u].mn[i], t[t[u].ls].mn[i]);
            t[u].mx[i] = max(t[u].mx[i], t[t[u].ls].mx[i]);
        }
        if (t[u].rs) {//右子树的最大最小值
            t[u].mn[i] = min(t[u].mn[i], t[t[u].rs].mn[i]);
            t[u].mx[i] = max(t[u].mx[i], t[t[u].rs].mx[i]);
        }
    }
    t[u].sum = t[t[u].ls].sum + t[t[u].rs].sum + t[u].tmp.w;
    t[u].siz = t[t[u].ls].siz + t[t[u].rs].siz + 1;
}

int build(int l, int r, int wd) {
    if (l > r) return 0;
    int u = newnode();
    int m = (l + r) >> 1;
    WD = wd; nth_element(p + l, p + m, p + r + 1);
    t[u].tmp = p[m];
    t[u].ls = build(l, m - 1, wd ^ 1);
    t[u].rs = build(m + 1, r, wd ^ 1);
    push_up(u);
    return u;
}

void pia(int u, int num) {//拍扁回炉重做
    if (t[u].ls) pia(t[u].ls, num);
    p[t[t[u].ls].siz + num + 1] = t[u].tmp, rub[++top] = u;
    if (t[u].rs) pia(t[u].rs, t[t[u].ls].siz + num + 1);
}

void check(int &u, int wd) {//检查是否平衡，不平衡则需要重建
    if (t[u].siz * alpha < t[t[u].ls].siz || t[u].siz * alpha < t[t[u].rs].siz) pia(u, 0), u = build(1, t[u].siz, wd);
}

void insert(int &u, node tp, int wd) {//插入点
    if (!u) {
        u = newnode();
        t[u].ls = t[u].rs = 0, t[u].tmp = tp;
        push_up(u);
        return;
    }
    if (tp.x[wd] <= t[u].tmp.x[wd]) insert(t[u].ls, tp, wd ^ 1);
    else insert(t[u].rs, tp, wd ^ 1);
    push_up(u);
    check(u, wd);
}

bool in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {//完全被包含
    return (x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2);
}

bool out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {//完全无交集
    return (x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1);
}

int query(int u, int x1, int y1, int x2, int y2) {
    if (!u) return 0;
    int res = 0;
    if (in(x1, y1, x2, y2, t[u].mn[0], t[u].mn[1], t[u].mx[0], t[u].mx[1])) return t[u].sum;
    if (out(x1, y1, x2, y2, t[u].mn[0], t[u].mn[1], t[u].mx[0], t[u].mx[1])) return 0;
    if (in(x1, y1, x2, y2, t[u].tmp.x[0], t[u].tmp.x[1], t[u].tmp.x[0], t[u].tmp.x[1])) res += t[u].tmp.w;
    res += query(t[u].ls, x1, y1, x2, y2) + query(t[u].rs, x1, y1, x2, y2);
    return res;
}

void init() {
    ans = rt = top = tot = 0;
}


void solve() {
    scanf("%d", &n);
    while(1) {
        int opt; scanf("%d",&opt);
        if(opt == 1) {
            int x, y, w; scanf("%d%d%d",&x,&y,&w);
            insert(rt, node{x ^ ans, y ^ ans, w ^ ans}, 0);
        }
        else if(opt == 2) {
            int x1, y1, x2, y2; scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            ans = query(rt, x1 ^ ans, y1 ^ ans, x2 ^ ans, y2 ^ ans);
            printf("%d\n",ans);
        }
        else break;
    }
}