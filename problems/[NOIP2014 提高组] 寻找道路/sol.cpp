#include<bits/stdc++.h>
using namespace std;
int n,m,s,t;
vector<int>g[100005],newg[100005];
bool vis[100005];
int dis[100005];
bool can[100005],ccan[100005];
void dfs(int s){
    for(auto v:g[s]){
        if(!vis[v]){
            vis[v]=1;
            can[v]=1;
            dfs(v);
        }
    }
}
void bfs(int s){
    queue<int>q;
    q.push(s);
    dis[s]=0;
    vis[s]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(auto v:newg[now]){
            if(!vis[v]&&!ccan[v]){
                dis[v]=dis[now]+1;
                vis[v]=1;
                q.push(v);
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        newg[u].push_back(v);
        g[v].push_back(u);
    }
    cin>>s>>t;
    vis[t]=1;
    can[t]=1;
    dfs(t);
    for(int i=1;i<=n;i++){
        for(auto v:newg[i]){
            if(!can[v]){
                ccan[i]=1;
                break;
            }
        }
    }
    memset(dis,-1,sizeof(dis));
    memset(vis,0,sizeof(vis));
    bfs(s);
    cout<<dis[t];
    return 0;
}