#include<iostream>
#include<cstdlib>
#include<ctime>
#define N 100005
using namespace std;
int n,m;
int ls[N],rs[N],siz[N],pri[N],val[N],rev[N];
int rt,tot;
void maintain(int x){
	siz[x]=siz[ls[x]]+siz[rs[x]]+1;
}
void spread(int p){
	if(rev[p]){
		swap(ls[p],rs[p]);
		if(ls[p]) rev[ls[p]]^=1;
		if(rs[p]) rev[rs[p]]^=1;
		rev[p]=0;
	}
}
void split(int p,int x,int &l,int &r){
	if(!p) {l=r=0;return;}
	spread(p);
	if(siz[ls[p]]+1<=x){
		l=p;
		split(rs[p],x-siz[ls[p]]-1,rs[p],r);
	}else{
		r=p;
		split(ls[p],x,l,ls[p]);
	}
	maintain(p);
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	spread(x);spread(y);
	if(pri[x]>pri[y]){
		rs[x]=merge(rs[x],y);
		maintain(x);
		return x;
	}else{
		ls[y]=merge(x,ls[y]);
		maintain(y);
		return y;
	}
}
void insert(int x){
	val[++tot]=x;
	pri[tot]=rand();
	siz[tot]=1;
	rt=merge(rt,tot);
}
void dfs(int p){
	spread(p);
	if(ls[p]) dfs(ls[p]);
	printf("%d ",val[p]);
	if(rs[p]) dfs(rs[p]);
}
int main(){
	srand(time(0));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) insert(i);
	while(m--){
		int l,r,x,t,y;
		scanf("%d%d",&l,&r);
		split(rt,r,x,y);
		split(x,l-1,x,t);
		rev[t]^=1;
		rt=merge(merge(x,t),y);
	}
	dfs(rt);
	return 0;
}
