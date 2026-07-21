#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int w[100005];
int dis1[100005],dis2[100005];
vector<int>g[100005];
int f[100005][4];
bool vis[100005];
int dis[2505][2505];
int ans;
void bfs(int s){
    queue<int>q;
    q.push(s);
    vis[s]=1;
    dis1[s]=0;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(auto v:g[now]){
            if(!vis[v]){
                vis[v]=1;
                dis1[v]=dis1[now]+1;
                q.push(v);
            }
        }
    }
}
void bfs2(int s){
    queue<int>q;
    q.push(s);
    dis2[s]=0;
    vis[s]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(auto v:g[now]){
            if(!vis[v]){
                vis[v]=1;
                dis2[v]=dis2[now]+1;
                dis[s][v]=dis2[v];
                q.push(v);
            }
        }
    }
}
signed main(){
    cin>>n>>m>>k;
    memset(dis,0x3f,sizeof(dis));
    memset(dis1, 0x3f, sizeof(dis1));
    for(int i=2;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs(1);
    memset(vis,0,sizeof(vis));
    for(int i=2;i<=n;i++){
        memset(vis,0,sizeof(vis));
        memset(dis2,0x3f3f3f3f,sizeof(dis2));
        bfs2(i);
        for(int j=2;j<=n;j++){
            if(dis1[j]<=k+1&&dis2[j]<=k+1&&j!=i){
                for(int h=1;h<=3;h++){
                    if(w[j]>w[f[i][h]]){
                        for(int gg=3;gg>=h+1;gg--){
                            f[i][gg]=f[i][gg-1];
                        }
                        f[i][h]=j;
                        break;
                    }
                    
                }
            }
        }
    }
    for(int i=2;i<=n;i++){
        for(int j=2;j<=n;j++){
            if(i==j||dis[i][j]>k+1)continue;
            for(int gg=1;gg<=3;gg++){
                for(int h=1;h<=3;h++){
                    if(f[i][gg] == 0 || f[j][h] == 0) continue;
                    if(f[i][gg]!=f[j][h]&&f[i][gg]!=j&&f[j][h]!=i){
                        ans=max(ans,w[f[i][gg]]+w[j]+w[i]+w[f[j][h]]);
                    }
                }
            }
        }
    }
    cout<<ans;
    return 0;
}