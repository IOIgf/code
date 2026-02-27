#include<bits/stdc++.h>
using namespace std;
const int N=1010;
vector<int>g[N];
vector<int>newg[N];
int dfn[N],low[N],ins[N],idx,n,m;
stack<int>stk;
int w[N];
int cnt,T;
bool vis[N],bian[N][N];
void init(){
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(ins,0,sizeof(ins));
    memset(vis,0,sizeof(vis));
    memset(bian,0,sizeof(bian));
    memset(newg,0,sizeof(newg));
    memset(w,0,sizeof(w));
    while(!stk.empty())stk.pop();
    idx=cnt=0;
    for(int i=1;i<=n;i++)g[i].clear(),newg[i].clear();
}
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	ins[u]=1;
	stk.push(u);
	for(auto v:g[u]){
		if(!dfn[v])tarjan(v);
		if(ins[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		while(1){
			int v=stk.top();
			ins[v]=0;
            w[v]=cnt;
			stk.pop();
			if(v==u)break;
		}
	}
}
void bfs(int u){
    queue<int>q;
    q.push(u);
    vis[u]=1;
    bian[u][u]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(auto v:newg[now]){
            q.push(v);
            bian[u][v]=1;
        }
    }
}
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            g[u].push_back(v);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i])tarjan(i);
        for(int u=1;u<=n;u++)
            for(auto v:g[u])
                if(w[u]!=w[v])newg[w[u]].push_back(w[v]);
        for(int i=1;i<=cnt;i++)
            bfs(i);
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=cnt;j++){
                if(!bian[i][j]&&!bian[j][i]){
                    cout<<"No"<<endl;
                    goto out;
                }
            }
        }
        cout<<"Yes"<<endl;
        out:
            continue;
    }
	return 0;
}