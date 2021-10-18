int ch[N][2], fa[N], rev[N], siz[N];//基本内容
int sum[N], val[N], tag[N];//另外要维护的
#define lc  ch[u][0]
#define rc  ch[u][1]
#define identify(u) (ch[fa[u]][1] == u)
#define isRoot(u)   (u != ch[fa[u]][0] && u != ch[fa[u]][1])
void flip(int u) { swap(lc, rc); rev[u] ^= 1; }
void push_up(int u) {
    siz[u] = siz[lc] + siz[rc] + 1;
    //...
}
void push_down(int u) {
    if (rev[u]) {
        if (lc) flip(lc);
        if (rc) flip(rc);
        rev[u] = 0;
    }
    //...
}
void update(int u) {//当前点之上的所有点都push_down
    if (!isRoot(u)) update(fa[u]);
    push_down(u);
}
void rotate(int u) {
    int f = fa[u], fc = identify(u);
    int g = fa[f], gc = identify(f);
    int uc = fc ^ 1, c = ch[u][uc];
    if (!isRoot(f))
        ch[g][gc] = u; fa[u] = g;
    ch[f][fc] = c, fa[c] = f;
    ch[u][uc] = f, fa[f] = u;
    push_up(f); push_up(u);
}
void splay(int u) {//将u变为u所在的Splay的根
    update(u);
    for (int f; f = fa[u], !isRoot(u); rotate(u))
        if (!isRoot(f)) rotate(identify(f) ^ identify(u) ? u : f);
}
int access(int u) {//将(rt, u)之间的路径变为实链
    int pre = 0;
    for (; u; u = fa[pre = u])
        splay(u), rc = pre, push_up(u);
    return pre;
}
void makeRoot(int u) {//将u变为整棵树的根(注意:不一定是当前splay的根)
    u = access(u);
    flip(u);
}
int findRoot(int u) {
    access(u), splay(u);
    while (lc) push_down(u), u = lc;
    splay(u);
    return u;
}
void link(int u, int v) {
    makeRoot(u); splay(u);
    if (findRoot(v) != u) fa[u] = v;
}
void split(int u, int v) {
    makeRoot(u);
    access(v); splay(v);//加了这个就将v变为splay的根
}
void cut(int u, int v) {
    makeRoot(u); splay(u);
    if (findRoot(v) == u && fa[v] == u && !ch[v][0]) {
        fa[v] = ch[u][1] = 0;
        push_up(u);
    }
}
void fix(int u, int k) {
    splay(u); val[u] = k;
}