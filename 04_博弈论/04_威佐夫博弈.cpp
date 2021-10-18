// 每次每个人可以从任意一堆石子中取任意多的石子或者从两堆石子中取同样多的石子，不能取得人输

void WZF() {
    int a, b;
    cin >> a >> b;
    if(a > b) swap(a, b);
    int temp = b - a;
    int ans = temp * (1.0 + sqrt(5.0)) / 2.0;
    if(ans == a)
        cout << "second" << endl;
    else 
        cout << "first" << endl;
}

void EX_WZF() {
    int a, b, k;
    cin >> a >> b >> k;
    k++;
    if(a > b) swap(a, b);
    int temp = (b - a) / k;
    int ans1 = temp * (2 - k + sqrt(4.0 + k * k)) / 2;
    int ans2 = temp * (2 + k + sqrt(4.0 + k * k)) / 2;
    if(ans1 == a && ans2 == b)
        cout << "second" << endl;
    else 
        cout << "first" << endl;
}
