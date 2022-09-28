struct node {
    int x, y, z;
};

struct UnionFind {
private:
    int rk[N], pre[N], siz[N], totNode;//N为最大点数
    stack<node> st;//node记录上次修改的内容
public:
    void init(int tot) {
        totNode = tot;
        for (int i = 1; i <= totNode; i++)
            pre[i] = i, siz[i] = rk[i] = 1;
    }
    int find(int x) { while (x ^ pre[x]) x = pre[x]; return x; }
    void merge(int x, int y) {//按秩合并
        x = find(x), y = find(y);
        if (x == y) return;
        if (rk[x] < rk[y]) swap(x, y);
        st.push(node{ y, rk[x], siz[y] });
        pre[y] = x, rk[x] += rk[x] == rk[y], siz[x] += siz[y];
    }
    int start() { return st.size(); }
    void end(int last) {//撤回merge操作
        while (st.size() > last) {
            node tp = st.top();
            rk[pre[tp.x]] -= tp.y, siz[pre[tp.x]] -= tp.z;
            pre[tp.x] = tp.x;
            st.pop();
        }
    }
    bool judge() { return siz[find(1)] == totNode; }
};
