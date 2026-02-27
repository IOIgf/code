#include<bits/stdc++.h>
using namespace std;
int n;
const int N=1e5+5;
vector<int> g[N];
int dfn[N],low[N],w[N],idx;
int ins[N],cnt;
stack<int> stk;
int rd[N];
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
    cin>>n;
    for(int i=1;i<=n;i++){
        int u;
        while(1){
            cin>>u;
            if(!u)break;
            g[i].push_back(u);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto v:g[i]){
            if(w[i]!=w[v])rd[w[v]]++;
        }
    }
    int ans=0;
    for(int i=1;i<=cnt;i++){
        if(rd[i]==0)ans++;
    }
    cout<<ans;
    return 0;
}