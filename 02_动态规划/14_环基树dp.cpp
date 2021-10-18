int flag, S, E;//flag是否找到环, SE为环上两个点

void findCircle(int u, int fa) {
    vis[u] = 1;
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa) {
            if (vis[v]) flag = 1, S = u, E = v;
            else findCircle(v, u);
        }
}

void dp(int u, int fa) {
    //dp过程

    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa && v) {
            dp(v, u);

        }
}

ll calc(int u) {
    flag = 0;
    findCircle(u, 0);
    if (flag) {
        for (int i = head[S], v; i; i = e[i].nxt)
            if ((v = e[i].to) == E) {
                e[i].to = e[i ^ 1].to = 0;//删边操作, 注意e[tot]中tot从2开始
                break;
            }
        ll res = 0;
        dp(S, 0); res = max(res, ...);
        dp(E, 0); res = max(res, ...);
        return res;
    }
    else {
        dp(u, 0);
        return ...;
    }
}
