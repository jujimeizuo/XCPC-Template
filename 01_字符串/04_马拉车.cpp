#include <iostream>
#include <cstdio>
#include <cstring>
#define Min(a,b) a>b?b:a
#define Max(a,b) a>b?a:b
using namespace std;
const int N = 2e6 + 10 ;
int Len[N] , a[N] ;
char str[N] ;
int n,mx,id,len;
string s ;
void init(int l , int r){
    
    int k=0;
    str[k++] = '$';
    for(int i=l;i<=r;i++){
    
        str[k++]='#';
        str[k++]=s[i];
    }
    str[k++]='#';
    len=k;
    str[k] = '\0' ;
}
int ans = 0 , flag ;
int Manacher(){
    
  Len[0] = 0;
  int sum = 0;
  mx = 0;
  id = 0 ;
  // cout << str << endl ;
  for(int i=1;i<len;i++){
    
    if(i < mx) Len[i] = Min(mx - i, Len[2 * id - i]);
    else Len[i] = 1;
    while(str[i - Len[i]]== str[i + Len[i]]) Len[i]++;
    if(Len[i] + i > mx){
            // 更新最长的回文串
      mx = Len[i] + i;          // mx是回文串右边一个位置
      id = i;             //id是回文串的中心
      sum = Max(sum, Len[i]);         // sum 是回文串的长度 + 1

    }
    // cout << i << " " << Len[i] << endl ;
    // if(Len[i] == i)  表示前缀是回文的
    //  {
    
    //    if(ans < Len[i])
    //     ans = Len[i] - 1 , flag = 1 ;
    //  }
    // if(Len[i] + i == len)  表示后缀是回文的
    //  if(ans < Len[i])
    //   ans = Len[i] - 1 , flag = 2 ;
  }
  return sum - 1 ;
}

int main()
{
    
  scanf("%d",&n);
  while(n--){
    
    cin >> s ;
    len = s.size();
    int l = 0 , r = len - 1 ;
    init(l , r);
    ans = 0 , flag = 0 ;
    // cout << Manacher() << endl ;
  }
  return 0;
}

