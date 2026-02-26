#include<bits/stdc++.h>
#define mk(a,b) make_pair(a,b)
using namespace std;
const int N=501000;
vector<pair<int,int>>e[N];
int dfn[N],low[N],ins[N],idx,n,m,ans;
stack<int>stk;
int cnt,scc[N],in[N],ww;
vector<pair<int,int>>g[N];
int u[N],v[N],dis[N];
int s,p;
bool vis[N];
void dfs(int u) {
	dfn[u]=low[u]=++idx;
	ins[u]=1;
	stk.push(u);
	for(auto [v,w]:e[u]) {
		if(!dfn[v])dfs(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]) {
		cnt++;
		while(1) {
			int v=stk.top();
			scc[v]=cnt;
			ins[v]=0;
			stk.pop();
			if(v==u)break;
		}
	}
}
void dij(int s){
	for(int i=1;i<=n;i++){
		dis[i]=(1<<31)-1;
	}
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
	q.push(mk(0,s));
	dis[s]=0;
	while(q.size()){
		int now=q.top().second;
		q.pop();
		if(vis[now])continue;
		vis[now]=1;
		for(auto [v,w]:g[now]){
			if(dis[v]>dis[now]+w){
				dis[v]=dis[now]+w;
				q.push(mk(dis[v],v));
			}
		}
	}
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		int u,v;
		cin>>u>>v>>ww;
		e[u].push_back(mk(v,-ww));
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			dfs(i);
		}
	}
	for(int u=1; u<=n; u++) {
		//if(!scc[u])continue;
		for(auto [v,w]:e[u]){
			if(scc[u]!=scc[v]) {
				g[scc[u]].push_back(mk(scc[v],w));
			}
		}
	}
	dij(scc[1]);
    cout<<dis[scc[n]]<<endl;
	return 0;
}