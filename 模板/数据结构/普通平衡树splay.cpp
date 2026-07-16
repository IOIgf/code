#include<iostream>
#define N 100005
#define ls son[p][0]
#define rs son[p][1]
using namespace std;
int n;
int fa[N],son[N][2],siz[N],val[N],cnt[N];
int rt,tot;
int get(int x){return x==son[fa[x]][1];}
void maintain(int p){siz[p]=siz[ls]+siz[rs]+cnt[p];}
void rotate(int p){
	int f=fa[p],g=fa[f],c=get(p);
	fa[p]=g; if(g)son[g][get(f)]=p;
	son[f][c]=son[p][c^1];
	if(son[p][c^1]) fa[son[p][c^1]]=f;
	son[p][c^1]=f;fa[f]=p;
	maintain(f);
	maintain(p);
}
inline void splay(int p){
	for(;fa[p];rotate(p)) 
		if(fa[fa[p]]) rotate(get(p)==get(fa[p])?fa[p]:p);
	rt=p;
}
int newnode(int x){
	int p=++tot;
	siz[p]=cnt[p]=1;
	val[p]=x;
	return p;
}
void insert(int x){
	if(!rt){
		rt=newnode(x);
		return;
	}
	int p=rt;
	while(1){
		if(val[p]==x){
			cnt[p]++,siz[p]++;
			splay(p);
			return;
		}
		if(val[p]<x) {
			if(!rs){
				rs=newnode(x);
				fa[tot]=p;
				splay(tot);
				return;
			}
			p=rs;
		}
		else {
			if(!ls){
				ls=newnode(x);
				fa[tot]=p;
				splay(tot);
				return;
			}
			p=ls;
		}
	}
}
int getrank(int x){
	int p=rt,now=0;
	while(1){
		if(x<val[p]) {
			p=ls;
			continue;
		}
		now+=siz[ls];
		if(x==val[p]){
			splay(p);
			return now+1;
		}
		now+=cnt[p];
		p=rs;
	}
}
int getval(int k){
	int p=rt;
	while(1){
		if(k<=siz[ls]) {
			p=ls;
			continue;
		}
		if(k<=siz[ls]+cnt[p]){
			splay(p);
			return val[p];
		}
		k-=siz[ls]+cnt[p];
		p=rs;
	}
}
int pre(){
	int p=son[rt][0];
	while(rs) p=rs;
	splay(p);
	return val[p]; 
}
int nxt(){
	int p=son[rt][1];
	while(ls) p=ls;
	splay(p);
	return val[p];
}
void del(int x){
	getrank(x);
	if(cnt[rt]>1) {
		cnt[rt]--,siz[rt]--;
		return;
	}
	int p=rt;
	if(!son[p][0]) {
		fa[son[p][1]]=0;
		rt=son[p][1];
		maintain(son[p][1]);
	}else{
		pre();
		fa[son[p][1]]=fa[p];
		son[rt][1]=son[p][1];
		maintain(rt);	
	}
}
int main(){
	scanf("%d",&n);
	while(n--){
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1) insert(x);
		if(op==2) del(x);
		if(op==3) printf("%d\n",getrank(x));
		if(op==4) printf("%d\n",getval(x));
		if(op==5) {
			insert(x);
			printf("%d\n",pre());
			del(x);
		}
		if(op==6) {
			insert(x);
			printf("%d\n",nxt());
			del(x);
		}
	}
	return 0;
}
