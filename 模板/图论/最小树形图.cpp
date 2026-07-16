#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,r;
int ls[N],rs[N],d[N],pre[N],val[N],tag[N];
int rt[N];
void spread(int p){
	if(tag[p]){
		if(ls[p]) val[ls[p]]+=tag[p],tag[ls[p]]+=tag[p];
		if(rs[p]) val[rs[p]]+=tag[p],tag[rs[p]]+=tag[p];
		tag[p]=0;
	}
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	spread(x),spread(y);
	if(val[x]>val[y]) swap(x,y);
	rs[x]=merge(rs[x],y);
	if(d[ls[x]]<d[rs[x]]) swap(ls[x],rs[x]);
	d[x]=d[rs[x]]+1;
	return x;
}
int fa[N];
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}
int st[N],top,ins[N];
int fa2[N],val2[N];
int main(){
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(x==y) continue;
		pre[i]=x,val[i]=z;
		rt[y]=merge(rt[y],i);
	}
	for(int i=1;i<n;i++){
		pre[++m]=i;val[m]=0x3f3f3f3f;
		rt[i+1]=merge(rt[i+1],m);
	}
	pre[++m]=n;val[m]=0x3f3f3f3f;
	rt[1]=merge(rt[1],m);
	for(int i=1;i<=n;i++) fa[i]=i;
	int cnt=n;
	st[++top]=r;ins[r]=1;
	long long ans=0;
	while(cnt>1){
		int y=get(pre[rt[st[top]]]);
		if(y==st[top]) {
			rt[y]=merge(ls[rt[y]],rs[rt[y]]);
			continue;
		}
		if(!ins[y]){
			st[++top]=y;
			ins[y]=top;
			continue;
		}
		n++;fa[n]=n;
		cnt-=top-ins[y];
		for(int i=ins[y];i<=top;i++){
			int x=st[i],v=val[rt[x]];
			ans+=v;
			fa2[x]=n,val2[x]=v;
			rt[x]=merge(ls[rt[x]],rs[rt[x]]);
			if(rt[x]) tag[rt[x]]-=v,val[rt[x]]-=v;
			rt[n]=merge(rt[n],rt[x]);
			fa[x]=n;
		}
		top=ins[y];
		st[top]=n;ins[n]=top;
	}
	for(int p=r;p;p=fa2[p]) ans-=val2[p];
	if(ans>=0x3f3f3f3f) puts("-1");
	else printf("%lld\n",ans);
	return 0;
}
