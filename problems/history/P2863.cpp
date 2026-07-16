#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int n,m;
vector<int>g[N];
int dfn[N],ins[N],low[N],idx,cnt;
stack<int>stk;
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	stk.push(u);
	ins[u]=1;
	for(auto v:g[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		int cntt=0;
		while(1){
			int v=stk.top();
			stk.pop();
			ins[v]=0;
			cntt++;
			if(u==v)break;
		}
		if(cntt>1)cnt++;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	cout<<cnt;
	return 0;
}
