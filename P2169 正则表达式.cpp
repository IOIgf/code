#include<bits/stdc++.h>
#define mk(a,b) make_pair(a,b)
using namespace std;
const int N=501000;
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m,ans;
stack<int>stk;
int w[N],vs[N];
int cnt,scc[N],in[N],ww[N];
vector<int>g[N];
int s,p;
bool vis[N];
void dfs(int u) {
	dfn[u]=low[u]=++idx;
	ins[u]=1;
	stk.push(u);
	for(auto v:e[u]) {
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
int main() {
	cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>w[i];
    for(int i=1;i<=n;i++)
        cin>>v[i];
	for(int i=1; i<=n; i++) {
		int d;
		cin>>d;
		e[i].push_back(d);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			dfs(i);
		}
	}
	for(int u=1; u<=n; u++) {
		//if(!scc[u])continue;
		for(auto v:e[u]){
			if(scc[u]!=scc[v]) {
				g[scc[u]].push_back(scc[v]);
			}
		}
	}
	return 0;
}