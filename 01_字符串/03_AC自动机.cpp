class Automaton {
public :
    std::vector<std::vector<int>> tr;
    std::vector<int> e;
    std::vector<int> fail;
    int tot;
    Automaton(int n) : tot(0), tr(n, std::vector<int>(26)), e(n), fail(n) {}
    Automaton(int m, std::vector<std::string> s) : Automaton(m) {
        for(int i = 0;i < (int) s.size(); i++) {
            insert(s[i]);
        }
        build();
    }

    void insert(std::string s) {
        int u = 0;
        for(int i = 0;i < (int) s.size(); i++) {
            if(!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;
            u = tr[u][s[i] - 'a'];
        }
        e[u]++;
    }

    void build() {
        std::queue<int> q;
        for(int i = 0;i < 26; i++) {
            if(tr[0][i]) q.push(tr[0][i]);
        }
        while(!q.empty()) {
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

    int query(std::string t) {
        int u = 0, ans = 0;
        for(int i = 0;i < (int) t.size(); i++) {
            u = tr[u][t[i] - 'a'];
            for(int j = u;j && e[j] != -1; j = fail[j]) {
                ans += e[j], e[j] = -1;
            }
        }
        return ans;
    }
};
