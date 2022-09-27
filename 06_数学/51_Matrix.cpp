template <typename T>
struct Matrix {
    const int n;
    std::vector<std::vector<T>> mat;

    Matrix(int n = 0) : n(n), mat(n, std::vector<T>(n)) {}
    Matrix(const std::vector<std::vector<T>> &rhs) : n(n) {
        mat = std::move(rhs);
    }
    Matrix(const Matrix<T> &rhs) : n(n) {
        mat = std::move(rhs.mat);
    }
    void identify() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = (i == j);
            }
        }
    }
    T getVal(const int& i, const int& j) { return mat[i][j]; }
    T size() { return n; }
    const Matrix operator+(const Matrix& rhs) {
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ret.mat[i][j] = mat[i][j] + rhs.mat[i][j];
            }
        }
        return ret;
    }
    const Matrix operator-(const Matrix& rhs) {
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ret[i][j] = mat[i][j] - rhs[i][j];
            }
        }
        return ret;
    }
    const Matrix operator*(const Matrix &rhs) {
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    ret.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        return ret;
    }
    const Matrix operator+() { return *this; }
    const Matrix operator-() {
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ret.mat[i][j] = -mat[i][j];
            }
        }
        return ret;
    }
    Matrix &operator+=(const Matrix &rhs) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] += rhs.mat[i][j];
            }
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &rhs) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] -= rhs.mat[i][j];
            }
        }
        return *this;
    }
    const Matrix operator*=(const Matrix &rhs) {
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    ret.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        return ret;
    }
};

template <typename T>
Martix power(Matrix<T> a, T b) {
    Matrix<T> res(2);
    res.mat[0][0] = res.mat[1][1] = 1;
    for (; b /= 2; a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}