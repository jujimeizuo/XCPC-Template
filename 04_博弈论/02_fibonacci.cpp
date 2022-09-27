template <typename T>
bool Fibonacci(const T& x) {
    std::unordered_map<int, bool> was;
    std::vector<int> fib(51);
    fib[1] = 1; fib[2] = 2;
    for (int i = 3; i <= 50; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        was[fib[i]] = true;
    }
    return !was[fib[x]];
}