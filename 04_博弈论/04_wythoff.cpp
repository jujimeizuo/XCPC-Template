template <typename T>
bool wythoff(T& a, T& b) {
    if (a > b) std::swap(a, b);
    T delta = b - a;
    T res = delta * (1.0 + sqrt(5.0)) / 2;
    return !(res == a);
}

template <typename T>
bool wythoff_exp(T& a, T& b, T& k) {
    k++;
    if (a > b) std::swap(a, b);
    T delta = (b - a) / k;
    T res1 = delta * (2 - k + sqrt(4.0 + k * k)) / 2;
    T res2 = delta * (2 + k + sqrt(4.0 + k * k)) / 2;
    return !(res1 == a && res2 == b);
}