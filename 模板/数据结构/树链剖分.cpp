//13:41~13:56
//初始就要取模 t[p].sum=a[rnk[l]]%P

#include<iostream>
#define N 200005
using namespace std;
int n,m,rt,P;
int a[N];
int head[N],nxt[N*2],ver[N*2],tot;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];head[x]=tot;
}
int fa[N],son[N],siz[N],dep[N];
void dfs1(int x,int p){
	fa[x]=p;siz[x]=1;dep[x]=dep[p]+1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];if(y==p) continue;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}
int dfn[N],rnk[N],cd,top[N];
void dfs2(int x,int tp){
	top[x]=tp;dfn[x]=++cd;rnk[cd]=x;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
struct SegmentTree{
	int l,r;
	long long sum,add;
}t[N*4];
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r) {t[p].sum=a[rnk[l]]%P;return;}//////// 
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].sum=(t[p*2].sum+t[p*2+1].sum)%P;
}
void spread(int p){
	if(t[p].add){
		t[p*2].add+=t[p].add;
		t[p*2+1].add+=t[p].add;
		t[p*2].sum+=t[p].add*(t[p*2].r-t[p*2].l+1);
		t[p*2+1].sum+=t[p].add*(t[p*2+1].r-t[p*2+1].l+1);
		t[p].add=0;
	}
}
void change(int p,int l,int r,long long k){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].add+=k;
		t[p].sum+=k*(t[p].r-t[p].l+1);
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) change(p*2,l,r,k);
	if(r>mid) change(p*2+1,l,r,k);
	t[p].sum=(t[p*2].sum+t[p*2+1].sum)%P;
}
long long ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	long long ans=0;
	if(l<=mid) ans=(ans+ask(p*2,l,r))%P;
	if(r>mid) ans=(ans+ask(p*2+1,l,r))%P;
	return ans;
}
void changeadd(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,dfn[top[x]],dfn[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y); 
	change(1,dfn[x],dfn[y],k);
}
long long query(int x,int y){
	long long ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=(ans+ask(1,dfn[top[x]],dfn[x]))%P;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y); 
	return (ans+ask(1,dfn[x],dfn[y]))%P;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&rt,&P);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs1(rt,0);
	dfs2(rt,rt);
	build(1,1,n);
	while(m--){
		int op,x,y,z;
		scanf("%d%d",&op,&x);
		if(op==1){
			scanf("%d%d",&y,&z);
			changeadd(x,y,z);
		}
		if(op==2){
			scanf("%d",&y);
			printf("%lld\n",query(x,y));
		}
		if(op==3) {
			scanf("%d",&z);
			change(1,dfn[x],dfn[x]+siz[x]-1,z);
		}
		if(op==4) printf("%lld\n",ask(1,dfn[x],dfn[x]+siz[x]-1));
	}
	return 0;
}
