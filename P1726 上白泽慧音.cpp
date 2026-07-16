#include<bits/stdc++.h>
using namespace std;
const int N=101000;
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m;
stack<int>stk;
vector<vector<int> >scc;
int cnt,maxn;
void dfs(int u){
	dfn[u]=low[u]=++idx;
	ins[u]=1;
	stk.push(u);
	for(auto v:e[u]){
		if(!dfn[v])dfs(v);
		if(ins[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		vector<int>c;
		++cnt;
		while(1){
			int v=stk.top();
			c.push_back(v);
			ins[v]=0;
			stk.pop();
			if(v==u)break;
		}
		maxn=max(maxn,int(c.size()));
		sort(c.begin(),c.end());
		scc.push_back(c);
	}
}
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v,t;
		cin>>u>>v>>t;
		e[u].push_back(v);
		if(t==2){
			e[v].push_back(u);
		}
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])dfs(i);
	}
	sort(scc.begin(),scc.end());
	cout<<maxn<<endl;
	for(auto c:scc){
		if(c.size()==maxn){
			for(auto u:c)cout<<u<<" ";
			return 0;
		}
	}
	return 0;
}