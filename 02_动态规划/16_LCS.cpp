#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> p(n + 1), q(n + 1);
  for(int i = 1;i <= n; i++) cin >> p[i];
  for(int i = 1;i <= n; i++) cin >> q[i];
  
  vector<int> id(n + 1);
  for(int i = 1;i <= n; i++) id[q[i]] = i;
  vector<int> lis;
  // 将b中与a中的元素相关的位置，从大到小push进lis中
  for(int i = 1;i <= n; i++) {
    vector<int> d;
    for(int j = p[i];j <= n; j += p[i]) {
      d.emplace_back(id[j]);
    }
    sort(d.begin(), d.end(), greater<int>());
    for(auto x : d) lis.emplace_back(x);
  }
   
  vector<int> f;
  f.push_back(lis[0]);
  for(int i = 1;i < (int)lis.size(); i++) {
    if(lis[i] > f.back()) f.push_back(lis[i]);
    else {
      int pos = lower_bound(f.begin(), f.end(), lis[i]) - f.begin();
      f[pos] = lis[i];
    }
  }
  
  cout << f.size() << endl;
}
