//prim算法求最小生成树（稠密图）

struct Prim {
    static const int N = 1e6 + 10;
    int n, m;
    double ans;
    struct Edge {
        int v, next;
        double w;
    }e[N << 1];
    int head[N << 1], cnt;
   struct node {
       int now;
       double d;
       bool operator < (const node& rhs) const {
           return d > rhs.d;
       }
   };

   void init() {
       memset(head, -1, sizeof head);
       cnt = ans = 0;
   }

   inline void add(int u, int v, double w) {
       e[cnt].v = v;
       e[cnt].w = w;
       e[cnt].next = head[u];
       head[u] = cnt++;
   }

   void prim() {
       vector<int> vis(n + 1);
       priority_queue<node> q; q.push({1, 0});
       int res = 0;
       while(!q.empty() && res <= n) {
           node p = q.top(); q.pop();
           int u = p.now;
           double dis = p.d;
           if(vis[u]) continue;
           vis[u] = 1, res++, ans += dis;
           for(int i = head[u]; ~i; i = e[i].next) {
               int v = e[i].v;
               if(!vis[v]) q.push({v, e[i].w});
           }
       }
   }
}pr;