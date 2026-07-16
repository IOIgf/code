/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 16:14:06 
 * @Last Modified by:   Milk_Dragon 
 * @Last Modified time: 2026-07-16 16:14:06 
 */
#include<bits/stdc++.h>
using namespace std;
int n,m,dis[200005],start;
vector<pair<int,int> >g[200005];
bool vis[200005];
void dij(int s){
    for(int i=1;i<=n;i++){
        dis[i]=(1<<31)-1;
    }
    dis[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
    q.push({0,s});
    while(!q.empty()){
        int now=q.top().second;
        q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(auto v:g[now]){
            if(dis[v.second]>dis[now]+v.first){
                dis[v.second]=dis[now]+v.first;
                q.push({dis[v.second],v.second});
            }
        }
    }
}
int main(){
    cin>>n>>m>>start;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({w,v});
        g[v].push_back({w,u});
    }
    dij(start);
    for(int i=1;i<=n;i++){
        cout<<dis[i]<<" ";
    }
    return 0;
}