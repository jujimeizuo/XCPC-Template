#include <bits/stdc++.h>
using namespace std;

struct Monotone_stack {
    static const int N = 1e5 + 10;
    int a[N];
    stack<int> s;
    int n;
    
    void read() {
        cin >> n;
        for(int i = 1;i <= n; i++) cin >> a[i];
    }

    void Monotone_min() {
        for(int i = 1;i <= n; i++) {
            if(s.empty() || s.top() >= a[i])
                s.push(a[i]);
            else {
                while(!s.empty() && s.top() < a[i]) {
                    cout << s.top() << endl;
                    s.pop();
                }
                s.push(a[i]);
            }
        }
        while(!s.empty()) { 
            cout << s.top() << endl;
            s.pop();
        }
    }

    void Monotone_max() {
        for(int i = 1;i <= n; i++) {
            if(s.empty() || s.top() <= a[i])
                s.push(a[i]);
            else {
                while(!s.empty() && s.top() > a[i]) {
                    cout << s.top() << endl;
                    s.pop();
                }
                s.push(a[i]);
            }
        }
        while(!s.empty()) {
            cout << s.top() << endl;
            s.pop();
        }
    }

}Worker;
