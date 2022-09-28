class Trie {
private :
    Trie* next[26] = {nullptr};
    int val;
public : 
    Trie() {}

    void insert(std::string& s) {
        Trie* root = this;
        for (char &c : s) {
            if (root -> next[c] == nullptr) {
                root -> next[c] = new Trie();
            }
            root = root -> next[c];
        }
        root -> val ++;
    }

    void del(std::string& s) {
        Trie* root = this;
        for (char &c : s) {
            root = root -> next[c];
        }
        root -> val --;
    }

    int search(std::string& s) {
        int ans = 0;
        Trie* root = this;
        for (char& c : s) {
            if (!root -> next[c]) break ;
            root = root -> next[c];
            ans += root -> val;
        }
        return ans;
    }
};