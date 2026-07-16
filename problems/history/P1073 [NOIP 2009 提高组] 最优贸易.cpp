#include<bits/stdc++.h>
using namespace std;
int n,m;
int w[100005];
vector<int> g[100005];
vector<int> gg[100005];
int minn[100005];
int maxn[100005];
bool vis[100005];
bool vis2[100005];
void bfs1(){
    queue<int> q;
    q.push(1);
    vis[1]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        //vis[now]=0;
        for(auto v:g[now]){
            minn[v]=min(minn[now],minn[v]);
            if(!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
    }
}
void bfs2(){
    queue<int> q;
    q.push(n);
    vis2[n]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        //vis[now]=0;
        for(auto v:gg[now]){
            maxn[v]=max(maxn[now],maxn[v]);
            if(!vis2[v]){
                vis2[v]=1;
                q.push(v);
            }
        }
    }
}
int ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
        minn[i]=maxn[i]=w[i];
    }
    minn[1]=maxn[1]=w[1];
    for(int i=1;i<=m;i++){
        int u,v,z;
        cin>>u>>v>>z;
        g[u].push_back(v);
        gg[v].push_back(u);
        if(z==2){
            g[v].push_back(u);
            gg[u].push_back(v);
        }
    }
    bfs1();
    //memset(vis,0,sizeof(vis));
    bfs2();
    for(int i=1;i<=n;i++){
        if(vis[i]&&vis2[i])
            ans=max(ans,maxn[i]-minn[i]);
    }
    cout<<ans<<endl;
    return 0;
}