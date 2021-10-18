typedef long long ll;

// 指针版

typedef struct _node {
    _node *child[26]; // 儿子节点
    _node *fail; // ！！！
    vector<int> exist; // 该节点是否存在完整的单词
    bool flag;
}node;

char T[1000005];
int n;

void insert(node *root, char *q) {
    node *tmp = root;
    int len = strlen(q);
    for(int i = 0;i < len; i++) {
        int v = q[i] - 'a';
        if(tmp -> child[v] == NULL) {
            node *temp = new node();
            tmp -> child[v] = temp;
        }
        tmp = tmp -> child[v];
    }
    tmp -> exist.push_back(len);
}

void build(node *root) {
    for(int i = 0;i < n; i++) {
        char p[1000005];
        cin >> p;
        insert(root, p); // 建立字典树
    }
    queue<node*> q; // BFS层次遍历

    for(int i = 0;i < 26; i++) { // 确定第一层的fail指针全部指向root节点
        if(root -> child[i]) {
            q.push(root -> child[i]);
            root -> child[i] -> fail = root;
        }
    }

    while(!q.empty()) {
        node *x = q.front();
        q.pop();
        for(int i = 0;i < 26; i++) {
            if(x -> child[i]) {
                node *y = x -> child[i];
                node *fafail = x -> fail;

                while(fafail && fafail -> child[i] == NULL) {
                    fafail = fafail -> fail;
                }

                if(fafail == NULL)
                    y -> fail = root;
                else
                    y -> fail = fafail -> child[i];

                q.push(y);
            }
        }
    }
}

ll query(node *root) {
    int len = strlen(T);
    ll ans = 0;
    node *tmp = root;
    for(int i = 0;i < len; i++) {
        int c = T[i] - 'a';
        while(tmp -> child[c] == NULL && tmp -> fail) {
            tmp = tmp -> fail;
        }
        if(tmp -> child[c] != NULL) {
            tmp = tmp -> child[c];
        }
        else
            continue;

        if(!tmp -> flag) {
            ans += tmp->exist.size();
            tmp->flag = true;

            if (tmp->exist.size()) {
                for (int j = 0; j < tmp->exist.size(); j++) {
                    int m = tmp->exist[j];
                    for (int k = i - m + 1; k <= i; k++) {
                        cout << T[k];
                    }
                    cout << endl;
                }
            }
        }
    }
    return ans;
}

void AC() {
    node *root = new node();
    build(root);
    query(root);
}

const int CHAR_NUM = 26; // 仅小写
const int N = 1e6 + 10;

int trie[N][CHAR_NUM], cnt;

int fail[N];

int val[N];

char T[N];
int n;

void Insert(char *s) {
    int len = strlen(s);
    int root = 0;
    for(int i = 0;i < len; i++) {
        int v = s[i] - 'a';
        if(!trie[root][v])
            trie[root][v] = ++cnt;
        root = trie[root][v];
    }
    val[root]++;
}

void Build() {
    for(int i = 0;i < n; i++) {
        char p[N];
        cin >> p;
        Insert(p);
    }

    queue<int> q;

    fail[0] = 0;
    for(int i = 0;i < 26; i++) {
        if(trie[0][i]) {
            q.push(trie[0][i]);
            fail[trie[0][i]] = 0;
        }
    }

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(int i = 0;i < 26; i++) {
            if(trie[now][i]) {
                fail[trie[now][i]] = trie[fail[now]][i];
                q.push(trie[now][i]);
            }
            else {
                trie[now][i] = trie[fail[now]][i];
            }
        }
    }
}

ll Query() {
    ll ans = 0;
    int len = strlen(T);
    int root = 0;
    for(int i = 0;i < len; i++) {
        int v = T[i] - 'a';
        root = trie[root][v];

        for(int j = root; j && val[j] != -1; j = fail[j]) {
            ans += val[j];
            val[j] = -1;
        }
    }
    return ans;
}

void Ac() {
    Build();
    Query();
}
