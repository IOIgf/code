#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=1e5+5;
vector<int> g[N];
int dfn[N],low[N],w[N],idx;
int ins[N],cnt;
stack<int> stk;
int rd[N],cd[N];
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	ins[u]=1;
	stk.push(u);
	for(auto v:g[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		while(1){
			int v=stk.top();
			stk.pop();
			w[v]=cnt;
			ins[v]=0;
			if(v==u)break;
		}
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
	if(cnt==1){
		cout<<1<<endl<<0;
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(auto v:g[i]){
			if(w[i]!=w[v])rd[w[v]]++,cd[w[i]]++;
		}
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=cnt;i++){
		if(rd[i]==0)ans1++;
		if(cd[i]==0)ans2++;
	}
	cout<<ans1;
	return 0;
}
