#include<iostream>
#define N 100005
using namespace std;
int n,m;
int fa[N],son[N][2],a[N],val[N],rev[N];
inline int get(int x){
	return x==son[fa[x]][1];
}
inline int isrt(int x){
	return x!=son[fa[x]][get(x)];
}
inline void maintain(int p){
	val[p]=val[son[p][0]]^val[son[p][1]]^a[p];
}
inline void reverse(int p){
	if(!p) return;
	rev[p]^=1;
	swap(son[p][0],son[p][1]);
}
inline void pushdown(int p){
	if(rev[p]){
		reverse(son[p][0]),reverse(son[p][1]);
		rev[p]=0;
	}
}
inline void pushup(int p){
	if(!isrt(p)) pushup(fa[p]);
	pushdown(p);
}
inline void rotate(int p){
	int f=fa[p],c=get(p);
	fa[p]=fa[f];if(!isrt(f)) son[fa[f]][get(f)]=p;
	son[f][c]=son[p][c^1];
	if(son[p][c^1]) fa[son[p][c^1]]=f;
	son[p][c^1]=f;fa[f]=p;
	maintain(f);
	maintain(p);
}
inline void splay(int p){
	pushup(p);
	for(;!isrt(p);rotate(p))
		if(!isrt(fa[p])) rotate(get(p)==get(fa[p])?fa[p]:p);
}
inline void access(int p){
	for(int pre=0;p;pre=p,p=fa[p]){
		splay(p);son[p][1]=pre;
		maintain(p);
	}
}
inline void makeroot(int p){
	access(p);splay(p);reverse(p);
}
inline int find(int p){
	access(p);splay(p);
	while(son[p][0]) pushdown(p),p=son[p][0];
	splay(p);return p;
}
inline void link(int x,int y){
	if(find(x)==find(y)) return;
	makeroot(x);fa[x]=y;
}
inline void cut(int x,int y){
	makeroot(x);access(y);splay(y);
	if(son[y][0]!=x||fa[x]!=y||son[x][1]) return;
	son[y][0]=fa[x]=0;maintain(y);
}
inline int query(int x,int y){
	makeroot(x);access(y);splay(y);
	return val[y];
}
inline void change(int x,int k){
	makeroot(x);a[x]=k;maintain(x);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	while(m--){
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if(op==0) printf("%d\n",query(x,y));
		if(op==1) link(x,y);
		if(op==2) cut(x,y);
		if(op==3) change(x,y);
	}
	return 0;
}

/*

21:35~21:45


*/
