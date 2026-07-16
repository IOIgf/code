#include<iostream>
#include<algorithm>
#define N 1000005
#define INF 0x3f3f3f3f
using namespace std;
int n,q,k;
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int head[N],nxt[N*2],ver[N*2],tot;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];head[x]=tot;
}
int fa[N],siz[N],dep[N],son[N];
void dfs1(int x,int p){
	fa[x]=p,siz[x]=1,dep[x]=dep[p]+1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];if(y==p) continue;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}
int dfn[N],top[N],cd;
void dfs2(int x,int tp){
	dfn[x]=++cd,top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y!=fa[x]&&y!=son[x]) dfs2(y,y);
	}
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) swap(x,y);
		y=fa[top[y]];
	}
	return dfn[x]<dfn[y]?x:y;
}
int h2[N],v2[N*2],n2[N*2],e2[N*2],t2;
void add2(int x,int y){
	v2[++t2]=y;e2[t2]=dep[y]-dep[x];
	n2[t2]=h2[x];h2[x]=t2;
}
bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
int a[N],st[N],tp,rt;
void build(){
	sort(a+1,a+k+1,cmp);
	rt=lca(a[1],a[k]);
	tp=1,st[1]=rt;h2[rt]=0;
	for(int i=1;i<=k;i++){
		if(a[i]==rt) continue;
		h2[a[i]]=0;
		int p=lca(st[tp],a[i]);
		if(p==st[tp]){
			st[++tp]=a[i];
			continue;
		}
		while(dep[p]<dep[st[tp-1]]){
			add2(st[tp-1],st[tp]);
			tp--;
		}
		if(p==st[tp-1]){
			add2(st[tp-1],st[tp]);
			st[tp]=a[i];
		}
		else if(dep[p]>dep[st[tp-1]]){
			h2[p]=0;add2(p,st[tp]);
			st[tp]=p;st[++tp]=a[i];
		}
	}
	for(int i=1;i<tp;i++) add2(st[i],st[i+1]);
}
int v[N],mx,mn;
long long sum;
int d1[N],d2[N],sz[N];
void dfs(int x){
	sz[x]=v[x];
	d1[x]=0,d2[x]=INF;
	if(v[x]) d2[x]=0;
	for(int i=h2[x];i;i=n2[i]){
		int y=v2[i],z=e2[i];
		dfs(y);sz[x]+=sz[y];
		sum+=1ll*sz[y]*(k-sz[y])*z;
		mx=max(mx,d1[x]+d1[y]+z);
		d1[x]=max(d1[x],d1[y]+z);
		if(v[x]) mn=min(mn,d2[y]+z);
		else{
			mn=min(mn,d2[x]+d2[y]+z);
			d2[x]=min(d2[x],d2[y]+z);
		}
	}
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs1(1,1);
	dfs2(1,0);
	q=read();
	while(q--){
		k=read();
		for(int i=1;i<=k;i++) a[i]=read(),v[a[i]]=1;
		build();
		sum=0,mn=INF,mx=-INF;
		dfs(rt);
		printf("%lld %d %d\n",sum,mn,mx);
		for(int i=1;i<=k;i++) v[a[i]]=0;
		t2=0;
	}
	return 0;
}


