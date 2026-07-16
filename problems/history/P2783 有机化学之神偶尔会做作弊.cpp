#include<bits/stdc++.h>
using namespace std;
const int N=10050;
int n,m;
int dfn[N],low[N],ins[N],idx;
stack<int>stk;
vector<int>g[N];
vector<int>gg[N];
int w[N],dist[N],jl;
int cnt,du[N];
bool vis[N][N];
int f[N][20],dep[N];
void tarjan(int u,int f){
    dfn[u]=low[u]=++idx;
    stk.push(u);
    for(auto v:g[u]){
        if(v==f)continue;
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else 
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        ++cnt;
        while(1){
            int v=stk.top();
            stk.pop();
            w[v]=cnt;
            if(u==v)break;
        }
    }
}
void dfs(int u,int fa){
    f[u][0]=fa;
    dep[u]=dep[fa]+1;
    for(auto v:gg[u]){
        if(v!=fa)
            dfs(v,u);
    }
}
void init(){
    for(int j=1;(1<<j)<=cnt;j++){
        for(int i=1;i<=cnt;i++){
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
}
int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    int t=log2(cnt);
    for(int i=t;i>=0;i--){
        if(dep[f[u][i]]>=dep[v])u=f[u][i];
    }
    if(u==v)return u;
    for(int i=t;i>=0;i--){
        if(f[u][i]!=f[v][i]){
            u=f[u][i];
            v=f[v][i];
        }
    }
    return f[u][0];
}
int tot;

void write(int t){
    if(t==0)return ;
    write(t/2);
    cout<<t%2;
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
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto v:g[i]){
            if(w[i]!=w[v]&&!vis[w[i]][w[v]]){
                vis[w[i]][w[v]]=1;
                gg[w[i]].push_back(w[v]);
            }
        }
    }
    dfs(1,0);
    init();
    cin>>tot;
    while(tot--){
        int a,b;
        cin>>a>>b;
        int ans=dep[w[a]]+dep[w[b]]-2*dep[lca(w[a],w[b])]+1;
        write(ans);
        cout<<endl;
    }
}