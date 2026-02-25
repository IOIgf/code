#include<bits/stdc++.h>
#define N 400005
#define ll long long
#define INF 0x3f3f3f3f3f3f3f
#define fi first
#define se second
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m;
vector<int> ver[N],ver2[N];

int dfn[N],low[N],cd;
int st[N],top,cnt;
void tarjan(int x){
	dfn[x]=low[x]=++cd;
	st[++top]=x;
	for(int y:ver[x]){
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				cnt++;int z;
				do{
					z=st[top--];
					ver2[n+cnt].push_back(z);
					ver2[z].push_back(n+cnt);
				}while(z!=y);
				ver2[n+cnt].push_back(x);
				ver2[x].push_back(n+cnt);
			}
		}else low[x]=min(low[x],dfn[y]);
	}
}
int fa[N],dep[N],siz[N];
int f[N],pos[N];
int ans,ansx,ansy;

void dfs(int x,int p){
	fa[x]=p;dep[x]=dep[p]+1;siz[x]=(x<=n);
	int mx1=0,mx2=0;
	for(int y:ver2[x]){
		if(y==p) continue;
		dfs(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[mx1]) mx2=mx1,mx1=y;
		else if(siz[y]>siz[mx2]) mx2=y;
	}
	if(x<=n){
		if(!mx1){
			f[x]=1,pos[x]=x;
			return;
		}
		f[x]=max(siz[x]-siz[mx1],f[mx1]);
		pos[x]=pos[mx1];
		if(max(n-siz[mx1],f[mx1])<=ans){
			ans=max(n-siz[mx1],f[mx1]);
			ansx=x,ansy=pos[mx1];
		}
		if(mx2&&max(n-siz[mx1]-siz[mx2],max(f[mx1],f[mx2]))<=ans){
			ans=max(n-siz[mx1]-siz[mx2],max(f[mx1],f[mx2]));
			ansx=pos[mx1],ansy=pos[mx2];
		}
	}else{
		int mx3=n-siz[x];
		for(int y:ver2[x]) if(y!=p&&y!=mx1&&y!=mx2) mx3=max(mx3,siz[y]);
		f[x]=max(siz[mx2],f[mx1]);
		pos[x]=pos[mx1];
		if(mx2&&max(mx3,max(f[mx1],f[mx2]))<=ans){
			ans=max(mx3,max(f[mx1],f[mx2]));
			ansx=pos[mx1],ansy=pos[mx2];
		}
	}
}
int vis[N];
int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	while(dep[y]>dep[x]) vis[y]=1,y=fa[y];
	while(x!=y) vis[x]=vis[y]=1,x=fa[x],y=fa[y];
	vis[x]=1;
	return x;
}
vector<int> ver3[N],V[N];
void dfs2(int x,int p,int rt){
	if(x<=n) V[rt].push_back(x);
	for(int y:ver2[x]) if(!vis[y]&&y!=p) dfs2(y,x,rt);
}
void build(int x,int y){
	int z=lca(x,y);
	for(int x=1;x<=n;x++){
		for(int y:ver[x]){
			int p=0;
			if(dep[x]==dep[y]) p=fa[x];
			else if(dep[x]>dep[y]) p=fa[x];
			else p=fa[y];
			if(vis[p]) ver3[x].push_back(y);
		}
		if(vis[fa[x]]||x==fa[z]||x==z) dfs2(x,0,x);
	}
}

int fa2[N],deg[N],rnk[N];
vector<int> ver4[N];

void dfs3(int x){
	dfn[x]=low[x]=++cd;rnk[cd]=x;
	for(int y:ver3[x]){
		if(!dfn[y]){
			fa2[y]=x;deg[x]++;dfs3(y);
			low[x]=min(low[x],low[y]);
		}else low[x]=min(low[x],dfn[y]);
	}
}
int ans2[N],vis2[N];
void dfs4(int x){
	ans2[++cd]=x;vis2[x]=1;
	for(int y:ver4[x]) if(!vis2[y]) dfs4(y);
}

void bipolar_orientation(int s,int t){
	for(int i=1;i<=n;i++) dfn[i]=low[i]=0;
	cd=0;
	dfs3(s);
	queue<int> q;
	for(int i=1;i<=n;i++) {
		if(!dfn[i]) continue;
		low[i]=rnk[low[i]];
		if(i!=t&&deg[i]==0) q.push(i);
	}
	while(q.size()){
		int x=q.front();q.pop();
		ver4[fa2[x]].push_back(x);
		ver4[low[x]].push_back(x);
		if(fa2[x]!=t&&--deg[fa2[x]]==0) q.push(fa2[x]);
	}
	top=0;
	for(int x=t;x;x=fa2[x]) st[++top]=x;
	cd=0;
	for(int i=top;i>=1;i--) dfs4(st[i]);
}

int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x),read(y);
		ver[x].push_back(y);
		ver[y].push_back(x);
	}
	tarjan(1);
	ans=n+1;
	dfs(1,0);
	build(ansx,ansy);
	bipolar_orientation(ansx,ansy);
	cout<<ans<<" "<<cd<<"\n";
	for(int i=1;i<=cd;i++){
		int x=ans2[i];
		cout<<V[x].size()<<" ";
		for(int y:V[x]) cout<<y<<" ";
		cout<<"\n";
	}
	return 0;
}






//17:13~18:39

