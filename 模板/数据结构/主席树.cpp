#include<iostream>
#include<algorithm>
#define N 200005
using namespace std;
int n,m,a[N];
int d[N],dt;
int ls[N*30],rs[N*30],siz[N*30];
int rt[N],tot;
int build(int l,int r){
	int p=++tot;
	if(l==r) return p;
	int mid=(l+r)/2;
	ls[p]=build(l,mid);
	rs[p]=build(mid+1,r);
	return p;
}
int insert(int q,int l,int r,int x){
	int p=++tot;
	siz[p]=siz[q]+1;
	if(l==r) return p;
	int mid=(l+r)/2;
	ls[p]=ls[q],rs[p]=rs[q];
	if(x<=mid) ls[p]=insert(ls[q],l,mid,x);
	else rs[p]=insert(rs[q],mid+1,r,x);
	return p;
}
int ask(int p,int q,int l,int r,int k){
	if(l==r) return l;
	int lcnt=siz[ls[q]]-siz[ls[p]],mid=(l+r)/2;
	if(lcnt>=k) return ask(ls[p],ls[q],l,mid,k);
	else return ask(rs[p],rs[q],mid+1,r,k-lcnt);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		d[++dt]=a[i];
	}
	sort(d+1,d+dt+1);
	dt=unique(d+1,d+dt+1)-d-1;
	rt[0]=build(1,dt);
	for(int i=1;i<=n;i++){
		int x=lower_bound(d+1,d+dt+1,a[i])-d;
		rt[i]=insert(rt[i-1],1,dt,x);
	}
	while(m--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",d[ask(rt[l-1],rt[r],1,dt,k)]);
	}
	return 0;
}

//18:45~18:52
