namespace FastIO {
    char gc(void) {
        const int S = 1 << 17;
        static char buf[S], *s = buf, *t = buf;
        if (s == t) t = buf + fread(s = buf, 1, S, stdin);
        if (s == t) return EOF;
        return *s++;
    }

    int read(void) {
        int a = 0, b = 1, c = gc();
        for (; !isdigit(c); c = gc()) b ^= (c == '-');
        for (; isdigit(c); c = gc()) a = a * 10 + c - '0';
        return b ? a : -a;
    }
}
using namespace FastIO;