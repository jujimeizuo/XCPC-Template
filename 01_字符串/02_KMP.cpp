const int maxn = 10000005;
int Next[maxn];
int slen, tlen;
char S[maxn], T[maxn];
void GetNext() {
    int j, k;
    j = 0;
    k = -1;
    Next[0] = -1;
    while(j < tlen) {
        if(k == -1 || T[j] == T[k]) {
            Next[++j] = ++k;
        }
        else
            k = Next[k];
        }
}
 
/*返回模式串T在主串S中c首次出现的位置 , 返回的位置是从0开始的*/
int KMP_Index() {
    int i = 0, j = 0;
    GetNext();
    while(i < slen && j < tlen) {
        if(j == -1 || S[i] == T[j]) i++, j++;
        else j = Next[j];
    }
    if(j == tlen) return i - tlen;
    else return -1;
}

 /*返回模式串T在字串中出现的次数*/
int KMP_Count() {
    int ans = 0;
    if(slen == 1 && tlen == 1) {
        if(S[0] == T[0])
            return 1;
        else 
            return 0;
    }
    GetNext();
    int j = 0;
    for(int i = 0;i < slen; i++) {
        while(j > 0 && S[i] != T[j]) {
            j = Next[j];
        }
        if(S[i] == T[j]) j++;
        if(j == tlen) {
            ans++;
            j = Next[j];
        }
        /*if(j ==tlen)
        {
            printf("%d ",i - j);
        }
        模式串在主串中所有的位置*/
        }
    return ans;
}
int main()
{
    cin >> S >> T;
    slen = strlen(S);
    tlen = strlen(T);
    cout << "返回模式串T在主串S中c首次出现的位置是: " << KMP_Index() << endl;
    cout << "返回模式串T在字串中出现的次数是: "<< KMP_Count() << endl;
    return 0;
}

/*----------------------------------*/

//预处理前缀数组,前缀数组用于在字符串失配时进行转跳
#define MAXN 35000
int pi[MAXN];//前缀函数
void prefix_function(string s){
    memset(pi,0,sizeof(pi));
    for(int i=1;i<s.size();i++){
        int p = pi[i-1];
        while(p>0&&s[p]!=s[i])p=pi[p-1];
        if(s[i]==s[p])  pi[i]=++p;
    }
    return ;
}

//KMP写法一,不需要预处理版本
//将两个字符串拼接,如果从前往后求前缀,如果前缀为模式串长度,则匹配成功
vector<int> kmp(string s1,string s2){
    vector<int> appear;
    string s = s2+'%'+s1;//ATTENTION!!这个百分号应该是不存在于s1和s2中的任字符
    for (int i = 1; i < s.size(); i++) {
        int p = pi[i - 1];
        while (p > 0 && s[i] != s[p]) p = pi[p - 1];
        if (s[i] == s[p]) p++;
        pi[i] = p;
        if(pi[i]==s2.size())
            appear.push_back(i-2-s2.size());//注意这里要根据字符串首字母为止为0或1进行微调
                                            //此时为1
    }
    return appear;
}

//KMP写法2,需要对模式串进行预处理
vector<int> kmp(string s1,string s2){
    vector<int> appear;
    int p=0;
    for(int i=0;i<s1.size();i++){
        while (p > 0 && s1[i] != s2[p]) p = pi[p - 1];
        if (s1[i] == s2[p]) p++;
        if(p==s2.size())
            appear.push_back(i+2-s2.size());//要注意同理
    }
    return appear;
}

