template<typename T>
class Trie {
private :
    Trie* next[2] = {nullptr};
    int val;
    const int maxl = 32;
public : 
    Trie() {}

    void insert(T x) {
        Trie* root = this;
        for(int i = maxl; i >= 0; i--) {
            int u = x >> i & 1;
            if(root -> next[u] == nullptr) root -> next[u] = new Trie();
            root = root -> next[u];
            root -> val ++;
        }
    }

    void del(T x) {
        Trie* root = this;
        for (int i = maxl; i >= 0; i--) {
            root = root -> next[x >> i & 1];
            root -> val --;
        }
    }

    T search(T x) {
        T ans = 0;
        Trie* root = this;
        for (int i = maxl; i >= 0; i--) {
            int u = x >> i & 1;
            if (root -> next[!u] && root -> next[!u] -> val) {
                ans += 1 << i;
                root = root -> next[!u];
            } else {
                root = root -> next[u];
            }
        }
        return ans;
    }
};