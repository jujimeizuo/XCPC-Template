using i128 = __int128;
 
std::istream &operator>>(std::istream &is, i128 &n) {
    n = 0;
    std::string s;
    is >> s;
    for (auto c : s) {
        n = 10 * n + c - '0';
    }
    return is;
}
 
std::ostream &operator<<(std::ostream &os, i128 n) {
    if (n == 0) {
        return os << 0;
    }
    std::string s;
    while (n > 0) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}
