#include<bits/stdc++.h>
using namespace std;
const int N=5010000;
vector<int>g[N];
int dfn[N],low[N],ins[N],idx,n,m,sz;
int cnt[N],fa[N];
bool vis[N];
//stack<int>stk;
vector<int>anss;
vector<vector<int> >ss;
void tarjan(int u,int f){
    bool fl=0;
	dfn[u]=low[u]=++idx;
	int ch=0;
    fa[u]=f;
	for(auto v:g[u]){
		if(!dfn[v]){
			tarjan(v,u);
			ch++;
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])cnt[v]=1;
		}
		else{
            if(v!=f||fl){
                low[u]=min(low[u],dfn[v]);
            }
            else fl=1;
        }
	}
	//if(f==0&&ch<=1)cnt[u]=0;
}
void dfs(int u){
    for(auto v:g[u]){
        if((fa[v]==u&&cnt[v])||(fa[u]==v&&cnt[v]))continue;
        if(!vis[v]){
            vis[v]=1;
            anss.push_back(v);
            dfs(v);
        }
    }
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])
			tarjan(i,0);
	}
    int ans=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
            anss.clear();
            vis[i]=1;
            anss.push_back(i);
            dfs(i);
            ss.push_back(anss);
            ans++;
        }
	}
    cout<<ans<<endl;
    for(auto c:ss){
        cout<<c.size()<<" ";
        for(auto v:c)cout<<v<<" ";
        cout<<endl;
    }
	puts("");
	return 0;
}