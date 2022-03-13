class Automaton {
public :
    const int n;
    std::vector<std::vector<int>> tr;
    std::vector<int> e;
    std::vector<int> fail;
    int tot;

    Automaton(int _n) : n(_n), tr(n, std::vector<int>(26)), e(n), fail(n), tot(0) {}
    Automaton(int m, std::vector<string> s) : Automaton(m) {
        for(int i = 0;i < (int) s.size(); i++) {
            insert(s[i]);
        }
        build();
    }

    void insert(string s) {
        int u = 0;
        for(int i = 0;i < (int) s.size(); i++) {
            if(!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;
            u = tr[u][s[i] - 'a'];
        }
        e[u]++;
    }

    void build() {
        queue<int> q;
        for(int i = 0;i < 26; i++) {
            if(tr[0][i]) q.push(tr[0][i]);        
        }
        while(q.size()) {
            int u = q.front();
            q.pop();
            for(int i = 0;i < 26; i++) {
                if(tr[u][i]) {
                    fail[tr[u][i]] = tr[fail[u]][i];
                    q.push(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    int query(string t) {
        int u = 0, res = 0;
        for(int i = 0;i < (int) t.size(); i++) {
            u = tr[u][t[i] - 'a'];
            for(int j = u;j && e[j] != -1; j = fail[j]) {
                res += e[j], e[j] = -1;
            }
        }
        return res;
    }
};
