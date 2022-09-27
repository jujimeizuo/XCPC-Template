// 求解a^x = b (mod c)，要求gcd(a, c) = 1， 不要求p为素数, x的范围是0 <= x <= p-1

template <typename T>
struct Hash {
    int n;
    int cnt;
    std::vector<int> head, next, hash, id;
    Hash(int _n) : n(_n), head(_n, -1), next(_n), id(_n), hash(_n), cnt(0) {}

    void insert(T x, T y) {
        T k = x % n;
        hash[cnt] = x;
        id[cnt] = y;
        next[cnt] = head[k];
        head[k] = cnt++;
    }

    T query(T x) {
        for(int i = head[x % n]; i != -1 ; i = next[i]){
            if(hash[i] == x)
                return id[i];
        }
        return -1;
    }
};

template <typename T>
T bsgs(T& a, T& b, T& c) {
    a %= c; b %= c;
    int cnt = 1;
    if (b == 1) return 0;
    Hash<long long> hs(100005);
    T m = std::ceil(sqrt((double) c));
    T x = 1, p = 1;
    for (T j = 0; j < m; j++, p = p * a % c) {
        hs.insert(p * b % c, j);
    }
    for (T i = 1, j; i <= m; i++) {
        x = x * p % c;
        if ((j = hs.query(x)) != -1) {
            return i * m - j;
        }
    }
    return -1;
}