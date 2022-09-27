template <typename T>
std::array<T, 3> exgcd(T a, T b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
    /*
    auto [g, x, y] = exgcd<long long>(a, b);
    assert(1LL * a * x + 1LL * b * y == g);
    if (c % g != 0) {
        std::cout << -1 << std::endl;
        continue ;
    }
    */
}