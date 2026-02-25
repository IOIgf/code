#include<iostream>
#define N 200005
using namespace std;
int n,m,a[N];
int cnt=1,rt[N],tot;
int sav[N*30],top;
int newnode(){
	if(top) return sav[top--];
	return ++tot;
}
int ls[N*30],rs[N*30];
long long siz[N*30];
int build(int l,int r){
	int p=newnode();
	if(l==r) {siz[p]=a[l];return p;}
	int mid=(l+r)/2;
	ls[p]=build(l,mid);
	rs[p]=build(mid+1,r);
	siz[p]=siz[ls[p]]+siz[rs[p]];
	return p;
}
int insert(int p,int l,int r,int x,int k){
	if(!p) p=newnode();
	siz[p]+=k;
	if(l==r) return p;
	int mid=(l+r)/2;
	if(x<=mid) ls[p]=insert(ls[p],l,mid,x,k);
	else rs[p]=insert(rs[p],mid+1,r,x,k);
	return p;
}
long long ask(int p,int l,int r,int L,int R){
	if(!p) return 0;
	if(L<=l&&r<=R) return siz[p];
	int mid=(l+r)/2;
	long long ans=0;
	if(L<=mid) ans+=ask(ls[p],l,mid,L,R);
	if(R>mid) ans+=ask(rs[p],mid+1,r,L,R);
	return ans;
}
int askkth(int p,int l,int r,long long k){
	if(l==r) return l;
	int mid=(l+r)/2;
	if(siz[ls[p]]>=k) return askkth(ls[p],l,mid,k);
	return askkth(rs[p],mid+1,r,k-siz[ls[p]]);
}
int merge(int p,int q,int l,int r){
	if(!p||!q) return p+q;
	siz[p]+=siz[q];
	if(l<r){
		int mid=(l+r)/2;
		ls[p]=merge(ls[p],ls[q],l,mid);
		rs[p]=merge(rs[p],rs[q],mid+1,r);
	}
	siz[q]=ls[q]=rs[q]=0;
	sav[++top]=q;
	return p;
}
void split(int &p,int &q,int l,int r,int L,int R){
	if(r<L||l>R||!p) return;
	if(L<=l&&r<=R){q=p,p=0;return;}
	q=newnode();
	int mid=(l+r)/2;
	if(L<=mid) split(ls[p],ls[q],l,mid,L,R);
	if(R>mid) split(rs[p],rs[q],mid+1,r,L,R);
	siz[p]=siz[ls[p]]+siz[rs[p]];
	siz[q]=siz[ls[q]]+siz[rs[q]];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	rt[1]=build(1,n);
	while(m--){
		int op,p,x,y;
		scanf("%d%d",&op,&p);
		if(op==0){
			scanf("%d%d",&x,&y);
			split(rt[p],rt[++cnt],1,n,x,y);
		}
		if(op==1){
			scanf("%d",&x);
			rt[p]=merge(rt[p],rt[x],1,n);
		}
		if(op==2){
			scanf("%d%d",&x,&y);
			rt[p]=insert(rt[p],1,n,y,x);
		}
		if(op==3){
			scanf("%d%d",&x,&y);
			printf("%lld\n",ask(rt[p],1,n,x,y));
		}
		if(op==4){
			long long k;
			scanf("%lld",&k);
			if(siz[rt[p]]<k) puts("-1");
			else printf("%d\n",askkth(rt[p],1,n,k));
		}
	}
	return 0;
}
