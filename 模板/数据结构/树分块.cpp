#include<bits/stdc++.h>
#define N 40005
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m;
const int B=200;
int val[N],d[N],dt;
vector<int> ver[N];
int fa[N],dep[N],dfn[N],siz[N],cd;

void dfs(int x,int p){
	dfn[x]=++cd;siz[x]=1;
	fa[x]=p;dep[x]=dep[p]+1;
	for(int y:ver[x]) if(y!=p) dfs(y,x),siz[x]+=siz[y];
}

int id[N],vis[N],anc[N];
int key[N],cnt;
bitset<N> f[205][205],F;

void dfs2(int x,int fa,int i){
	int lst=F[val[x]];
	F[val[x]]=1;
	if(vis[x]) f[i][vis[x]]=F;
	for(int y:ver[x]){
		if(y==fa) continue;
		dfs2(y,x,i);
	}
	F[val[x]]=lst;
}

void insert(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y]){
		F[val[x]]=1;
		x=fa[x];
	}
	while(x!=y){
		F[val[x]]=F[val[y]]=1;
		x=fa[x],y=fa[y];
	}
	F[val[x]]=1;
}

int main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(val[i]);
		d[++dt]=val[i];
	}
	sort(d+1,d+dt+1);
	dt=unique(d+1,d+dt+1)-d-1;
	for(int i=1;i<=n;i++) val[i]=lower_bound(d+1,d+dt+1,val[i])-d;
	for(int i=1;i<n;i++){
		int x,y;
		read(x),read(y);
		ver[x].push_back(y);
		ver[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+n+1,[&](int i,int j){return dep[i]>dep[j];});
	vis[1]=1;
	cnt=1,key[1]=1;
	for(int i=1;i<=n;i++){
		int x=id[i],y=x;
		for(int j=1;j<=B;j++){
			if(vis[y]) break;
			y=fa[y];
		}
		if(!vis[y]) {
			vis[y]=++cnt;
			key[cnt]=y;
		}
		anc[x]=y;
	}
	for(int i=1;i<=cnt;i++) dfs2(key[i],0,i);
	
	int lst=0;
	while(m--){
		int x,y;
		read(x),read(y);
		x^=lst;
		F.reset();
		int x2=anc[x],y2=anc[y];
		if(dfn[x2]>dfn[y2]) swap(x,y),swap(x2,y2);
		if(x2==y2) insert(x,y);
		else if(dfn[x2]<dfn[y2]&&dfn[y2]<dfn[x2]+siz[x2]){
			int z=y2;
			while(anc[fa[z]]!=x2) z=anc[fa[z]];
			F=f[vis[y2]][vis[z]];
			insert(y,y2);
			insert(x,z);
		}else{
			F=f[vis[x2]][vis[y2]];
			insert(x,x2);
			insert(y,y2);
		}
		lst=F.count();
		cout<<lst<<"\n";
	}
	return 0;
}


