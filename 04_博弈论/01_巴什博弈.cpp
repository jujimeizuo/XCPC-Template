// 一堆石头，一次只能拿m个
void BaShe() {
    int n, m;
    cin >> n >> m;
    if(n % (m + 1))
        cout << "first" << endl;
    else 
        cout << "second" << endl;
}
