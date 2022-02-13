template<class Info>
struct LinearBasis {
    const int n;
    int size;
    long long num;
    // 每个异或值都相同的个数都为2^n-r,所以不同的异或值有2^r个. 
    const int maxl = 61;
    std::vector<long long> a, v;
    LinearBasis(int n) : n(n), size(0), a(maxl) {}
    LinearBasis(std::vector<Info> init) : LinearBasis(init.size()) {
        auto insert = [&](long long t) {
            for (int i = maxl - 1; i >= 0; --i) {
                if (!(t >> i & 1)) continue;
                if (a[i]) t ^= a[i];
                else {
                    ++size;
                    // Rebuild 
                    for (int j = i - 1; j >= 0; --j) if (t >> j & 1) t ^= a[j];
                    for (int j = i + 1; j < maxl; ++j) if (a[j] >> i & 1) a[j] ^= t;
                    //
                    a[i] = t;
                    return;
                }
            }
        };
        for(int i = 0;i < n; i++) insert(init[i]);
        auto basis = [&]() {
            for (int i = 0; i < maxl; ++i) if (a[i]) v.push_back(i);
        };
        basis();
        num = 1LL << size;
    }

    // 查询能否xor出x这个数
    bool find(long long x) {
        for(int i = maxl - 1;i >= 0; i--) {
            if(x >> i & 1) {
                if(!a[i]) return false;
                x ^= a[i];
            }
        }
        return true;
    }

    // 查询异或最大值
    long long askmax() {
        long long ans = 0;
        for(int i = maxl - 1;i >= 0; i--) ans = max(ans, ans ^ a[i]);
        return ans;
    }

    // 查询异或最小值
    long long askmin() {
        if((int) v.size() < n) return 0;
        for(int i = 0;i < maxl; i++) if(a[i]) return a[i];
        return 0;
    }

    // 查询异或第k小
    long long askmink(long long x) {
        if(v.size() != n) x--;
        if(!x) return 0;
        if(x >= (1LL << v.size())) return -1;
        long long ans = 0;
        for(int i = 0;i < (int) v.size(); i++) {
            if(x >> i & 1) ans ^= a[v[i]];
        }
        return ans;
    }

    long long rank(long long x) {
        long long ret = 0;
        for (int i = 0; i < (int) v.size(); ++i) if (x >> v[i] & 1) ret += 1LL << i;
        return ret;
    }
};
