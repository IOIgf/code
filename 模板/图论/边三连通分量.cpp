#include<bits/stdc++.h>
#define N 1000005
#define ll unsigned long long
using namespace std;
template<typename T> inline void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
mt19937 rd(time(0));

int n,m;
int head[N],nxt[N],ver[N],tot=1;
void add(int x,int y){
	ver[++tot]=y;nxt[tot]=head[x];head[x]=tot;
}
int vis[N],vis2[N],fa[N],dep[N];
void dfs(int x,int i2){
	vis[x]=vis2[i2/2]=1;
	fa[x]=ver[i2^1];dep[x]=dep[fa[x]]+1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!vis[y]) dfs(y,i);
	}
}
ll h[N],val[N],h2[N];
map<ll,int> mp,mp2,mp3;

void dfs2(int x,int i2){
	vis[x]=2;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(vis[y]==1) dfs2(y,i),val[x]^=val[y];
	}
	ll hs=((ll)rd()<<32)+rd();
	if(mp[val[x]]) h2[x]^=hs;
	else{
		if(mp2[val[x]]) {
			h2[mp2[val[x]]]^=hs;
			h2[x]^=hs;
		}
		mp2[val[x]]=x;
	}
}
vector<int> ans[N];
int cnt;
void dfs3(int x){
	h2[x]^=h2[fa[x]];vis[x]=3;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(vis[y]==2) dfs3(y);
	}
}

int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x);
	}
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
	for(int i=1;i<=m;i++){
		if(vis2[i]) continue;
		int x=ver[i*2],y=ver[i*2+1];
		h[i]=((ll)rd()<<32)+rd();
		val[x]^=h[i],val[y]^=h[i];
		mp[h[i]]=1;
	}
	mp[0]=1;
	for(int i=1;i<=n;i++) if(vis[i]==1) dfs2(i,0);
	for(int i=1;i<=n;i++) if(vis[i]==2) dfs3(i);
	for(int i=1;i<=n;i++){
		if(!mp3[h2[i]]) mp3[h2[i]]=++cnt;
		ans[mp3[h2[i]]].push_back(i);
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++){
		for(int x:ans[i]) cout<<x<<" ";
		cout<<"\n";
	}
	return 0;
}

/*

边三连通分量不一定连通
 


*/
