/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 16:14:42 
 * @Last Modified by:   Milk_Dragon 
 * @Last Modified time: 2026-07-16 16:14:42 
 */
#include<bits/stdc++.h>
using namespace std;
int n,m,s;
int deep[500005];
vector<int>g[500005];
int f[500005][25];
void dfs(int s,int fa){
    f[s][0]=fa;
    deep[s]=deep[fa]+1;
    for(auto v:g[s]){
        if(fa==v)continue;
        dfs(v,s);
    }
}
int lca(int a,int b){
    if(deep[a]<deep[b])swap(a,b);
    for(int i=22;i>=0;i--){
        if(deep[f[a][i]]>=deep[b]){
            a=f[a][i];
        }
    }
    if(a==b)return a;
    for(int i=22;i>=0;i--){
        if(f[a][i]!=f[b][i]){
            a=f[a][i];
            b=f[b][i];
        }
    }
    return f[a][0];
}
int main(){
    cin>>n>>m>>s;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(s,0);
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
    while(m--){
        int a,b;
        cin>>a>>b;
        cout<<lca(a,b)<<endl;
    }
    return 0;
}