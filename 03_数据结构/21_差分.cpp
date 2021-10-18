#include <bits/stdc++.h>

using namespace std;

/*------------------一维差分--------------------*/

//可以区间修改，更改的值必须一样
int f[1005]; // 原始数组
int d[1005]; // 差分数组，原始数组的相邻元素之间的差值

int n;

void init() {
    for(int i = 1;i <= n; i++) {
        d[i] = f[i] - f[i - 1];
    }
}

void update(int l, int r, int k) {
    d[l] += k;
    d[r + 1] -= k;
}

void merge() {
    for(int i = 1;i <= n; i++) {
        d[i] = d[i] + d[i - 1];
    }
}

/*---------------二维差分------------------*/
const int N = 1005;

int mp[N][N];
int p[N][N];
int n, m;

void init() {

    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= m; j++) {
            p[i][j] = mp[i][j] - mp[i - 1][j] - mp[i][j - 1] + mp[i - 1][j - 1];
        }
    }
}

void update(int x1, int y1, int x2, int y2, int k) {
    p[x1][y1] += k;
    p[x1][y2 + 1] -= k;
    p[x2 + 1][y1] -= k;
    p[x2 + 1][y2 + 1] += k;
}

void merge() {

    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= m; j++) {
            p[i][j] = p[i][j] + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
        }
    }
}

// 求区间交
// len存的是各线段长度
int Interval_crossing() {
    vector<pii> res;
    for(auto item : len) {
        res.push_back(pii{item.fi, 1});
        res.push_back(pii{item.se + 1, -1});
    }
    sort(res.begin(), res.end());
    int tag = 0, lst = 0, ans = 0;
    for(auto i : res) {
        if(tag == n) ans += i.fi - lst;
        tag += i.se;
        lst = i.fi;
    }
    return ans;    
}