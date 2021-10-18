//https://ac.nowcoder.com/acm/contest/view-submission?submissionId=44654655

struct KM {
#define type int
    //#define inf 0x3f3f3f3f
    static const int N = 505;
    static const int INF = 0x3f3f3f3f;
    int n, mx[N], my[N], prv[N];
    type slk[N], lx[N], ly[N], w[N][N];
    bool vx[N], vy[N];

    void init(int siz) {
        n = siz;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                w[i][j] = -505;
            }
        }
    }

    void add_edge(int x, int y, type val) { w[x][y] = val; }

    void match(int y) { while (y) swap(y, mx[my[y] = prv[y]]); }

    void bfs(int x) {
        int i, y;
        type d;
        for (i = 1; i <= n; i++) {
            vx[i] = vy[i] = 0;
            slk[i] = INF;
        }
        queue<int> q;
        q.push(x);
        vx[x] = 1;
        while (1) {
            while (!q.empty()) {
                x = q.front();
                q.pop();
                for (y = 1; y <= n; y++) {
                    d = lx[x] + ly[y] - w[x][y];
                    if (!vy[y] && d <= slk[y]) {
                        prv[y] = x;
                        if (!d) {
                            if (!my[y]) return match(y);
                            q.push(my[y]);
                            vx[my[y]] = 1;
                            vy[y] = 1;
                        } else slk[y] = d;
                    }
                }
            }
            d = INF + 1;
            for (i = 1; i <= n; i++) {
                if (!vy[i] && slk[i] < d) {
                    d = slk[i];
                    y = i;
                }
            }
            for (i = 1; i <= n; i++) {
                if (vx[i]) lx[i] -= d;
                if (vy[i]) ly[i] += d;
                else slk[i] -= d;
            }
            if (!my[y]) return match(y);
            q.push(my[y]);
            vx[my[y]] = 1;
            vy[y] = 1;
        }
    }

    type max_match() {
        int i;
        type res;
        for (i = 1; i <= n; i++) {
            mx[i] = my[i] = ly[i] = 0;
            lx[i] = *max_element(w[i] + 1, w[i] + n + 1);
        }
        for (i = 1; i <= n; i++) bfs(i);
        res = 0;
        for (i = 1; i <= n; i++) res += lx[i] + ly[i];
        return res;
    }

#undef type
};