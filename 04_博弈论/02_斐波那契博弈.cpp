int fib[100001], n;
map<int, bool> p;
int main() {
    fib[1] = 1; fib[2] = 2;
    for(int i = 3;i <= 50; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        p[fib[i]] = 1;
    }
    scanf("%d",&n);
    if(p[n]) printf("second");
    else printf("first");
}
