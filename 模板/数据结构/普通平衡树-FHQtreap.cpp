#include<iostream>
#include<cstdlib>
#include<ctime>
#define N 1200005
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int n,m,a[N];
int ls[N],rs[N],val[N],pri[N],siz[N];
int rt,tot,lst;
inline void maintain(int x){
	siz[x]=siz[ls[x]]+siz[rs[x]]+1;
}
int newnode(int x){
	val[++tot]=x;
	pri[tot]=rand();
	siz[tot]=1;
	return tot;
}
void split(int p,int x,int &l,int &r){
	if(!p){l=r=0;return;}
	if(val[p]<=x){
		l=p;
		split(rs[p],x,rs[p],r);
	}
	else{
		r=p;
		split(ls[p],x,l,ls[p]);
	}
	maintain(p);
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(pri[x]>pri[y]){
		rs[x]=merge(rs[x],y);
		maintain(x);
		return x;
	}
	else{
		ls[y]=merge(x,ls[y]);
		maintain(y);
		return y;
	}
}
void insert(int x){
	int l,r,t=newnode(x);
	split(rt,x,l,r);
	rt=merge(merge(l,t),r);
}
void del(int x){
	int l,t,r;
	split(rt,x,l,r);
	split(l,x-1,l,t);
	rt=merge(merge(l,ls[t]),merge(rs[t],r));
}
void getrank(int x){
	int l,r;
	split(rt,x-1,l,r);
	lst=siz[l]+1;
	rt=merge(l,r);
}
int getval(int p,int k){
	if(k==siz[ls[p]]+1) return val[p];
	if(k<=siz[ls[p]]) return getval(ls[p],k);
	return getval(rs[p],k-siz[ls[p]]-1);
}
void getpre(int x){
	int l,r;
	split(rt,x-1,l,r);
	lst=getval(l,siz[l]);
	rt=merge(l,r);
}
void getnxt(int x){
	int l,r;
	split(rt,x,l,r);
	lst=getval(r,1);
	rt=merge(l,r);
}
int main(){
	srand(time(0));
	n=read(),m=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
		insert(a[i]); 
	}
	int ans=0;
	while(m--){
		int op=read(),x=read();
		x^=lst;
		if(op==1) insert(x);
		if(op==2) del(x);
		if(op==3) getrank(x);
		if(op==4) lst=getval(rt,x);
		if(op==5) getpre(x);
		if(op==6) getnxt(x);
		if(op>2) ans^=lst;
	}
	printf("%d\n",ans);
	return 0;
}

