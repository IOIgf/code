#include<bits/stdc++.h>
using namespace std;
const int N=5001000;
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m,sz;
int cnt;
stack<int>stk;
vector<int>ans[N];
void dfs(int u,int f){
	dfn[u]=low[u]=++idx;
	int ch=0;
	stk.push(u);
	for(auto v:e[u]){
		if(!dfn[v]){
			ch++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				cnt++;
				//stk.pop();
				while(1){
					ans[cnt].push_back(stk.top());
				
					if(stk.top()==v){
						stk.pop();
						break;
					}	stk.pop();
				}
				ans[cnt].push_back(u);
			}
		}
		else if(v!=f){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(f==0&&ch==0)ans[++cnt].push_back(u);
	//sz+=cnt[u];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
        if(e[i].size()==0)continue;
		if(!dfn[i]){
			while(stk.size()!=0){
				stk.pop();
			}
			dfs(i,0);
		}
	}
	cout<<cnt<<endl;
	//puts("");
	return 0;
}
