#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int cnt[N], idx;
int trie[N][26];

void insert(string s) {
    int len = s.length();
    int root = 0;
    for(int i = 0;i < len; i++) {
        int v = s[i] - 'a';
        if(!trie[root][v]) trie[root][v] =++idx;
        root = trie[root][v];
    }
    cnt[root]++;
}

int query(string s) {
    int ans = 0;
    int len = s.length();
    int root = 0;
    for(int i = 0;i < len; i++) {
        int v = s[i] - 'a';
        if(!trie[root][v]) break;
        root = trie[root][v];
        ans += cnt[root];
    }
    return ans;
}

void solve()
{
    int n, m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n; i++) {
        char s[N];
        scanf("%s",s);
        insert(s);
    }
    while(m--) {
        char s[N];
        scanf("%s",s);
        printf("%d\n",query(s));
    }
}