int a[505][505];

void solve() {
    memset(a,0,sizeof(a));
    a[1][1]  = 1;
    a[2][1] = 1;
    int s,plus = 0;
    for(int i = 3;i < 491;i++){
        for(int j = 1;j < 491;j++){
            s = a[i-2][j]+a[i-1][j]+plus;
            a[i][j] = s % 10;
            plus = s / 10;
        }
    }
    int n;
    while(scanf("%d",&n) && n != -1) {
        int k = 491;
        while(1) {
            if(a[n][k]) break;
            k--;
        }
        while(k >= 1) {
            printf("%d",a[n][k]);
            k--;
        }
    }
}