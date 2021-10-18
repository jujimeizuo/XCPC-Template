#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
struct Base{
	int a[31],cnt;
	void clear(){memset(a,0,sizeof a),cnt=0;}
	void ins(int x){
		if(cnt==30) return;
		for(int i=29;i>=0&&x;i--) if(x>>i&1){
			if(a[i]) x^=a[i];
			else {a[i]=x,cnt++;return;}
		}
	}
	void merge(const Base &B){
		for(int i=29;i>=0;i--) if(B.a[i]) ins(B.a[i]);
	}
}t[maxn<<2];
int n,m,a[maxn],b[maxn];
int arr[maxn];
void upd(int i,int v){for(;i<=n;i+=i&-i) arr[i]^=v;}
int qxor(int i){int s=0;for(;i;i-=i&-i) s^=arr[i];return s;}
void upd(int i){t[i]=t[i<<1],t[i].merge(t[i<<1|1]);}
void build(int i,int l,int r){
	if(l==r) return t[i].ins(b[l]);
	int mid=(l+r)>>1;
	build(i<<1,l,mid),build(i<<1|1,mid+1,r);
	upd(i);
}
void mdf(int i,int l,int r,int x){
	if(l==r) {t[i].clear(),t[i].ins(b[x]);return;}
	int mid=(l+r)>>1;
	x<=mid?mdf(i<<1,l,mid,x):mdf(i<<1|1,mid+1,r,x);
	upd(i);
}
void qry(int i,int l,int r,int x,int y){
	if(x<=l&&r<=y) return t[0].merge(t[i]);
	int mid=(l+r)>>1;
	if(x<=mid) qry(i<<1,l,mid,x,y);
	if(y>mid) qry(i<<1|1,mid+1,r,x,y);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i]^a[i-1],upd(i,b[i]);
	build(1,1,n);
	for(int op,l,r,x;m--;){
		scanf("%d%d%d",&op,&l,&r);
		if(op==1){
			scanf("%d",&x);
			upd(l,x),upd(r+1,x),b[l]^=x,b[r+1]^=x;
			mdf(1,1,n,l); if(r<n) mdf(1,1,n,r+1);
		}
		else{
			t[0].clear(),t[0].ins(qxor(l)); if(l<r) qry(1,1,n,l+1,r);
			printf("%d\n",1<<t[0].cnt);
		}
	}
}
