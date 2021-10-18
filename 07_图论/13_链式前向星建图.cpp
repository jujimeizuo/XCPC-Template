const int N = 1e5 + 10;

struct Edge {
    int v, w, next;
}e[N];

int head[N], cnt;

inline void add(int u, int v, int w) {
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

//在二分匹配的时候进行删边操作优化时间复杂度
//在250 * 50的图上能优化100ms左右
inline int del(int x)
{
    if (x == 0)
        return 0;
    int k = del(e[x].next);
    e[x].next = k;
    if ("表达式说明要删")
        return k;
    else
        return x;
}
// for (int i = 1; i < t; i++)
// {
//     del(head[i]);
// }
