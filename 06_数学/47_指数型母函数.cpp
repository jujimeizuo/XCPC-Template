
// 需要借助e^x的泰勒展开，一般求解多重排列数，即有 种物品，已知每种物品的数量为 k1,k2,...,kn 个，求从中选出m件物品的排列数。

// 对n个元素全排列，方案数为n!/(n1!n2!...nk!)，对n个中的r个元素进行全排列，这里就用到了指数型母函数，即G(x)=(1+x/1!+x^2/2!+...+x^k1/k1!)(1+x/1!+x^2/2!+...+x^k2/k2!)...(1+x/1!+x^2/2!+...+x^kn/kn!)

// 化简得G(x)=a0 + a1*x+a2*x^2/2!+...+ap*x^p/p!   (p = k1+k2+k3+...) ai为选出i个物品的排列方案数

//  若题目有规定条件，比如需要物品i出现非0的偶数次，即原式为(x^2/2!+x^4/4!+...+x^ki/ki!) 

#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

double num[15]; // 每种物品的数量，第i个物品有num[i]个

double a[15], b[15];

double f[120]; // 阶乘

void fac()
{
    f[0] = 1;
    for(int i = 1;i <= 105; i++)
        f[i] = f[i - 1] * i;
}

void Calc() {
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n; i++)
        cin >> num[i];

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    for(int i = 0;i <= num[1]; i++) {
        a[i] = 1.0 / f[i];
    }

    for(int i = 2;i <= n; i++) {
        for(int j = 0;j <= m; j++) {
            for(int k = 0;k <= num[i] && j + k <= m; k++) {
                b[j + k] += a[j] / f[k];
            }
        }

        for(int j = 0;j <= m; j++) {
            a[j] = b[j];
            b[j] = 0;
        }
    }

    cout << a[m] * f[m] << endl;
}