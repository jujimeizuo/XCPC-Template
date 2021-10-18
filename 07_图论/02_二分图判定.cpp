//不存在奇环即为二分图

const int N = 1e5 + 10;
bool flag;
int n;
vector <int> v[N], col(N);
void dfs(int x, int y){
  col[x] = y;
  for (int i = 0; i < v[x].size(); i++) {
     if (!col[v[x][i]]) dfs(v[x][i],3 - y);
     if (col[v[x][i]] == col[x]) flag = true;      //产生了冲突
  }
}

void check() {
    memset(col, 0, sizeof col);
    for(int i = 1;i <= n; i++) {
        if(!col[i]) dfs(i, 1); // dfs染色
    }
    if(flag) cout << "no";
    else cout << "yes";
}
