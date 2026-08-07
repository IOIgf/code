#include<bits/stdc++.h>
using namespace std;
const int N=101000;
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m;
stack<int>stk;
int cnt,scc[N],in[N],w[N];
vector<int>g[N],gg[N];
int u[N],v[N];
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
            gg[cnt].push_back(v);
			stk.pop();
			if(v==u)break;
        }
	}
}
int f[N];
int cd[N];
int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		cin>>u[i]>>v[i];
		e[u[i]].push_back(v[i]);
	}
	for(int i=1; i<=n; i++) 
		if(!dfn[i])dfs(i);
	for(int i=cnt;i>=1;i--){
        sort(gg[i].begin(),gg[i].end());
        for(auto v:gg[i]){
            cout<<v<<" ";
        }
        cout<<endl;
    }
	return 0;
}