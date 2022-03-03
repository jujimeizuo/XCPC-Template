class KMP {
public :
    const int n, m;
    std::string s, t;
    std::vector<int> next;
    std::vector<int> ans;
    KMP(string _s, string _t) : n(_s.size()), m(_t.size()), s(_s), t(_t), next(t.size() + 1) {
        for(int i = 1, j = 0;i < m; i++) {
            while(j > 0 && _t[j] != _t[i]) j = next[j];
            if(_t[j] == _t[i]) j++;
            next[i + 1] = j;
        }
    }
    void match() {
        if(m == 0 || n == 0) ans.push_back(0);
        for(int i = 0, j = 0;i < n; i++) {
            while(j > 0 && s[i] != t[j]) j = next[j];
            if(s[i] == t[j]) j++;
            if(j == m) ans.push_back(i - m + 1);
        }
    }
    int first() { return ans.size() == 0 ? -1 : ans.front(); }
    int size() { return (int) ans.size(); }
};
