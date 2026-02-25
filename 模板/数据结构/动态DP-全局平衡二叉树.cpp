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
int fa1[N],dep[N],siz[N],son[N];
void dfs1(int x,int p){
	fa1[x]=p,siz[x]=1;dep[x]=dep[p]+1;
	for(int y:ver[x]){
		if(y==p) continue;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}

int f[N][2];
struct Matrix{
	int a[2][2];
	int* operator [](int x){
		return a[x];
	}
}g[N];
Matrix operator *(Matrix a,Matrix b){
	Matrix c;
	c[0][0]=max(a[0][0]+b[0][0],a[0][1]+b[1][0]);
	c[0][1]=max(a[0][0]+b[0][1],a[0][1]+b[1][1]);
	c[1][0]=max(a[1][0]+b[0][0],a[1][1]+b[1][0]);
	c[1][1]=max(a[1][0]+b[0][1],a[1][1]+b[1][1]);
	return c;
}
int ls[N],rs[N],fa[N];
int st[N],top;
int sum[N];

void update(int p){
	g[p][0][0]=g[p][1][0]=f[p][0];
	g[p][0][1]=f[p][1];
	g[p][1][1]=-INF;
	g[p]=g[rs[p]]*g[p]*g[ls[p]];
}

int build2(int L,int R){
	if(L>R) return 0;
	if(L==R) {
		update(st[L]);
		return st[L];
	}
	int mid=lower_bound(sum+L,sum+R+1,(sum[R]+sum[L-1])/2)-sum;
	int p=st[mid];
	ls[p]=build2(L,mid-1);
	if(ls[p]) fa[ls[p]]=p;
	rs[p]=build2(mid+1,R);
	if(rs[p]) fa[rs[p]]=p;
	update(p);
	return p;
}

int build(int x){
	for(int t=x;t;t=son[t]){
		for(int y:ver[t]){
			if(y!=son[t]&&y!=fa1[t]) {
				int p=build(y);
				fa[p]=t;
				f[t][0]+=max(g[p][0][0],g[p][0][1]);
				f[t][1]+=g[p][0][0];
			}
		}
	}
	top=0;
	for(int t=x;t;t=son[t]) st[++top]=t;
	for(int i=1;i<=top;i++) sum[i]=sum[i-1]+siz[st[i]]-siz[son[st[i]]];
	return build2(1,top);
}

void change(int x,int k){
	f[x][1]+=k-a[x];
	a[x]=k;
	for(;x;x=fa[x]){
		int p=fa[x];
		if(p&&x!=ls[p]&&x!=rs[p]){
			f[p][0]-=max(g[x][0][0],g[x][0][1]);
			f[p][1]-=g[x][0][0];
		}
		update(x);
		if(p&&x!=ls[p]&&x!=rs[p]){
			f[p][0]+=max(g[x][0][0],g[x][0][1]);
			f[p][1]+=g[x][0][0];
		}
	}
}

int main(){
	g[0][0][1]=g[0][1][0]=-INF;
	read(n),read(m);
	for(int i=1;i<=n;i++) read(a[i]),f[i][1]=a[i];
	for(int i=2;i<=n;i++){
		int x,y;
		read(x),read(y);
		ver[x].push_back(y);
		ver[y].push_back(x);
	}
	dfs1(1,0);
	int rt=build(1);
	int lst=0;
	while(m--){
		int x,y;
		read(x),read(y);
		x^=lst;
		change(x,y);
		lst=max(g[rt][0][0],g[rt][0][1]);
		cout<<lst<<"\n";
	}
	return 0;
}

//14:48

//全局平衡二叉树


 

