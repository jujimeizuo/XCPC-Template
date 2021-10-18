// 普通型母函数：（1+x^1+x^2+...）(1+x^2+x^4)(1+x^3+x^6..)(...)(...)... 类似整数拆分

// a_n=1,1,1,1... = \frac{1}{1-x}
// a_n=1,0,1,0... = \frac{1}{1-x^2}
// a_n=1,2,3,4... = \frac{1}{(1-x)^2}
// a_n=C(m,n)     = (1+x)^m
// a_n=C(m+n,n)   = \frac{1}{(1-x)^{m+1}}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 求解硬币等普通问题

const int N = 1e5 + 10;

int a[N]; // 权重为i的组合数，a[P]为答案
int b[N]; // 辅助数组
int P; // 需要被分解的数
int k; // 物品个数
int v[N]; // 每个物品的权重
int n1[N]; // 对于每种物品起始的因子（所需要的每个物品最小个数），最小为0
int n2[N]; // 对于每种物品最终的因子（所需要的每个物品最大个数），最大为INF

// 模板一(标准)

void Calc1() {
    memset(a, 0, sizeof(a));
    a[0] = 1;

    for(int i = 1;i <= k; i++) { // 枚举每个物品因子
        memset(b, 0, sizeof(b));
        for(int j = n1[i];j <= n2[i] && j * v[i] <= P; j++) { // 每个物品从最小因子到最大因子循环,如果n2是无穷的，则j<=n2[i]可以删去
            for(int m = 0;m + j * v[i] <= P; m++) { // 循环a的每个项
                b[m + j * v[i]] += a[m]; // 把结果加到对应项里，有点dp的味道
            }
        }
        memcpy(a, b, sizeof(b));
    }
}

// 模板二（数据量大的时候可以用，快速）

void Calc2() {
    memset(a, 0, sizeof(a));
    a[0] = 1;
    int last = 0;
    for(int i = 1; i <= k; i++) {
        int last2 = min(last + n2[i] * v[i], P);//计算下一次的last
        memset(b, 0, sizeof(int) * (last2 + 1));//只清空b[0..last2]
        for(int j = n1[i]; j <= n2[i] && j * v[i] <= last2; j++) //last2
            for(int m = 0; m <= last && m + j * v[i] <= last2; m++) //一个是last，一个是last2
                b[m + j * v[i]] += a[m];
        memcpy(a, b, sizeof(int) * (last2 + 1));//b赋值给a，只赋值0..last2
        last = last2;//更新last
    }
}
