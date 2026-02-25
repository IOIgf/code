#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
template<typename T> inline void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m;
vector<int> ver[N],ver2[N];

int vis[N],rnk[N],cd;
void dfs1(int x){
	vis[x]=1;
	for(int y:ver[x]) if(!vis[y]) dfs1(y);
	rnk[++cd]=x;
}
int cnt;
vector<int> scc[N];
void dfs2(int x){
	vis[x]=2;scc[cnt].push_back(x);
	for(int y:ver2[x]) if(vis[y]==1) dfs2(y);
}
void kosaraju(){
	for(int i=0;i<n;i++) if(!vis[i]) dfs1(i);
	for(int i=n;i>=0;i--) if(vis[rnk[i]]==1) cnt++,dfs2(rnk[i]);
}

int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x),read(y);
		ver[x].push_back(y);
		ver2[y].push_back(x);
	}
	kosaraju();
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++){
		cout<<scc[i].size()<<" ";
		for(int x:scc[i]) cout<<x<<" ";
		cout<<"\n";
	}
	return 0;
}

