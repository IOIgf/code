#include<bits/stdc++.h>
using namespace std;
const int N=101000;
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m;
stack<int>stk;
int cnt,scc[N];
vector<int>sc[N];
void dfs(int u){
	dfn[u]=low[u]=++idx;
	ins[u]=1;
	stk.push(u);
	for(auto v:e[u]){
		if(!dfn[v])dfs(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		cnt++;
		while(1){
			int v=stk.top();
			scc[v]=cnt;
			ins[v]=0;
			sc[cnt].push_back(v);
			stk.pop();
			if(v==u)break;
		}
		sort(sc[cnt].begin(),sc[cnt].end());
	}
}
vector<pair<int,int>>o;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])dfs(i);
	}
	for(int i=1;i<=cnt;i++){
		o.push_back({sc[i][0],i});
	}
	sort(o.begin(),o.end());
	for(auto&p:o){
		int id=p.second;
		for(int i=0;i<sc[id].size();i++){
			if(i)cout<<" ";
			cout<<sc[id][i];
		}
		cout<<"\n";
	}
	return 0;
}
