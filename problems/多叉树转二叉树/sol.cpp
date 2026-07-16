/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 21:29:05 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 21:53:06
 */
//https://newoj.daimayuan.top/p/P1536?tid=6749d305a42c919d13e6c9a0
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>g[100005];
int l[100005],r[100005];
void build(int s){
    if(g[s].size()==0)return;
    int siz=g[s].size();
    sort(g[s].begin(),g[s].end());
    l[s]=g[s][0];
    for(int i=1;i<g[s].size();i++){
        r[g[s][i-1]]=g[s][i];
    }
    for(auto v:g[s])build(v);
}
void dfs(int s){
    
    cout<<s<<" ";
    if(l[s]!=0)
    dfs(l[s]);
    if(r[s]!=0)
    dfs(r[s]);
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    build(1);
    dfs(1);
    return 0;
}