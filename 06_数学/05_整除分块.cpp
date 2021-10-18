int calc(int n, int m) {
    //\sum_{i = 1} ^ {m} n / i
    //向下取整
    for (int l = 1, r; l <= m; l = r + 1) {
        if (n / l) r = min(m, n / (n / l));
        else r = m;
        //[l, r]之间的 n / l 都相等
    }

    //向上取整
    for (int l = 1, r; l <= m; l = r + 1) {
        int t = (n + l - 1) / l;
        if (t == 1) r = m;
        else r = min(m, (n - 1) / (t - 1));
        //[l, r]之间的 (n + l - 1) / l 都相等
    }

}
