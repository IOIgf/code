#include<bits/stdc++.h>
#define N 100005
#define ll long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m,q;
vector<int> ver1[N],ver2[N];
int deg[N];
int fa[N],f[N][20],dep[N];
vector<int> son[N];
int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=19;i>=0;i--) if(dep[f[y][i]]>=dep[x]) y=f[y][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int qu[N],siz[N];

int main(){
	read(n);
	for(int i=1;i<=n;i++){
		int x;
		read(x);
		while(x){
			ver1[x].push_back(i);
			ver2[i].push_back(x);
			deg[i]++;
			read(x);
		}
	}
	int l=1,r=0;
	for(int i=1;i<=n;i++) {
		if(deg[i]==0) {
			qu[++r]=i;
			ver2[i].push_back(0);	
		}
	}
	while(l<=r){
		int x=qu[l++];
		fa[x]=ver2[x][0];
		for(int i=1;i<ver2[x].size();i++) fa[x]=lca(fa[x],ver2[x][i]);
		f[x][0]=fa[x],dep[x]=dep[fa[x]]+1;
		for(int i=1;i<20;i++) f[x][i]=f[f[x][i-1]][i-1];
		for(int y:ver1[x]) if(--deg[y]==0) qu[++r]=y;
	}
	for(int i=n;i>=1;i--){
		int x=qu[i];
		siz[x]++;
		siz[fa[x]]+=siz[x];
	}
	for(int i=1;i<=n;i++) cout<<siz[i]-1<<"\n";
	return 0;
}



