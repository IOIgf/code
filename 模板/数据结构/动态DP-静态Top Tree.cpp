#include<bits/stdc++.h>
#define ll long long
#define N 1000005
#define INF 0x3f3f3f3f
using namespace std;

template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m,a[N];
vector<int> ver[N];

struct Data{
	int a[2][2];
	int* operator [](int x){
		return a[x];
	}
};
inline int max(int a,int b){
	return a<b?b:a;
}
inline Data Compress(Data &a,Data &b){
	Data c;
	c[0][0]=max(a[0][0]+b[0][0],a[0][1]+b[1][0]);
	c[0][1]=max(a[0][0]+b[0][1],a[0][1]+b[1][1]);
	c[1][0]=max(a[1][0]+b[0][0],a[1][1]+b[1][0]);
	c[1][1]=max(a[1][0]+b[0][1],a[1][1]+b[1][1]);
	return c;
}
inline Data Rake(Data &a,Data &b){
	Data c;
	c[0][0]=a[0][0]+max(b[0][0],b[0][1]);
	c[0][1]=a[0][1]+max(b[0][0],b[0][1]);
	c[1][0]=a[1][0]+max(b[1][0],b[1][1]);
	c[1][1]=a[1][1]+max(b[1][0],b[1][1]);
	return c;
}
inline Data init(int k){
	Data a;
	a[0][0]=a[1][0]=0,a[0][1]=k;
	a[1][1]=-INF;
	return a;
}
struct TopTree{
	int ls,rs,fa,op,sz;
	Data val;
}t[N*2];
int tot;

inline void update(int p){
	t[p].sz=t[t[p].ls].sz+t[t[p].rs].sz;
	if(t[p].op) t[p].val=Compress(t[t[p].ls].val,t[t[p].rs].val);
	else t[p].val=Rake(t[t[p].ls].val,t[t[p].rs].val);
}
inline int merge(int x,int y,int f){
	int p=++tot;
	t[p].ls=x,t[p].rs=y;t[x].fa=t[y].fa=p;t[p].op=f;
	update(p);
	return p;
}

int fa1[N],dep[N],siz[N],son[N];
void dfs1(int x,int p){
	fa1[x]=p,siz[x]=1;dep[x]=dep[p]+1;
	for(int y:ver[x]){
		if(y==p) continue;
		t[y].val=init(a[y]);
		t[y].sz=1;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}

int build2(vector<int> &b,int l,int r,int f){
	if(l==r) return b[l];
	int mid=l,sum=0,now=t[b[l]].sz;
	for(int i=l;i<=r;i++) sum+=t[b[i]].sz;
	while(mid<r-1&&now*2<sum) now+=t[b[++mid]].sz;
	return merge(build2(b,l,mid,f),build2(b,mid+1,r,f),f);
}

int build(int x){
	vector<int> b1;
	if(x!=n+1) b1.push_back(x);
	for(;son[x];x=son[x]){
		vector<int> b2;
		for(int y:ver[x])
			if(y!=son[x]&&y!=fa1[x]) b2.push_back(build(y));
		if(!b2.size()) b1.push_back(son[x]);
		else b1.push_back(merge(son[x],build2(b2,0,b2.size()-1,0),0));
	}
	return build2(b1,0,b1.size()-1,1);
}

void change(int x,int k){
	t[x].val=init(k),a[x]=k;
	for(x=t[x].fa;x;x=t[x].fa) update(x);
}

int main(){
	read(n),read(m);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=2;i<=n;i++){
		int x,y;
		read(x),read(y);
		ver[x].push_back(y);
		ver[y].push_back(x);
	}
	ver[1].push_back(n+1);
	ver[n+1].push_back(1);
	tot=n;
	dfs1(n+1,0);
	int rt=build(n+1),lst=0;
	while(m--){
		int x,y;
		read(x),read(y);
		x^=lst;
		change(x,y);
		lst=max(t[rt].val[0][0],t[rt].val[0][1]);
		cout<<lst<<"\n";
	}
	return 0;
}


