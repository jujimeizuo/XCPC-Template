// S(n, m) = \sum_{i=0}^mC(n, i)

int x, y;
ll s;
ll S(int n, int m) {
    while(y < m) (s = s + C(x, ++y)) %= mod;
    while(y > m) (s = s - C(x, y--)) %= mod;
    while(x < n) (s = s * 2 - C(x++, y)) %= mod;
    while(x > n) (s = (s + C(--x, y)) * inv2) %= mod;
    return s;
}

