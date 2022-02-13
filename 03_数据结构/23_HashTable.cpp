template<typename T>
class HashTable{
private :
    const int maxn;
    std::vector<std::vector<T>> key, val;

public :
    HashTable(int n) : maxn(n), key(n), val(n) {}

    int hash(int x){
        return (((long long)x * (x + 1)) ^ x) % maxn;
    }
    void insert(int x){
        int u = hash(x);
        for(int v = 0; v < (int)key[u].size(); ++v)
            if(key[u][v] == x){
                ++val[u][v];
                return;
            }
        key[u].push_back(x), val[u].push_back(1);
    }
    T query(int x){
        int u = hash(x);
        for(int v = 0; v < (int)key[u].size(); ++v)
            if(key[u][v] == x)
                return val[u][v];
        return 0;
    }
};
