#include<bits/stdc++.h>
using namespace std;
const int N=5050;
int n,m;
int dfn[N],low[N],ins[N],idx;
stack<int>stk;
vector<int>g[N];
vector<int>gg[N];
int w[N],ans;
int cnt,du[N];
bool vis[N][N];
void tarjan(int u,int f){
    dfn[u]=low[u]=++idx;
    ins[u]=1;
    stk.push(u);
    for(auto v:g[u]){
        if(v==f)continue;
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(ins[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        ++cnt;
        while(1){
            int v=stk.top();
            ins[v]=0;
            stk.pop();
            w[v]=cnt;
            if(u==v)break;
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
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto v:g[i]){
            if(w[i]!=w[v]&&!vis[w[i]][w[v]]){
                vis[w[i]][w[v]]=1;
                vis[w[v]][w[i]]=1;
                gg[w[i]].push_back(w[v]);
                du[w[i]]++;
                du[w[v]]++;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        if(du[i]==1)ans++;
    }
    cout<<(ans+1)/2<<endl;
}