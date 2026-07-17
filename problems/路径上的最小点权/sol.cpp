/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-17 08:59:05 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-17 09:33:11
 */
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int aa[100005];
int deep[100005],f[100005][25];
vector<int>g[100005];
int minn[100005][25];
int ans;
void dfs(int s,int fa){
    deep[s]=deep[fa]+1;
    f[s][0]=fa;
    minn[s][0]=min(aa[s],aa[fa]);
    for(auto v:g[s]){
        if(v==fa)continue;
        dfs(v,s);
    }
}
int lca(int a,int b){
    int ans=min(aa[b],aa[a]);
    int ja=a,jb=b;
    if(deep[a]<deep[b])swap(a,b);
    for(int i=22;i>=0;i--){
        if(deep[f[a][i]]>=deep[b]){
            ans=min(ans,minn[a][i]);
            a=f[a][i];
        }
    }
    if(a==b){
        return ans;
    }
    for(int i=22;i>=0;i--){
        if(f[a][i]!=f[b][i]){
            ans=min(min(minn[a][i],minn[b][i]),ans);
            a=f[a][i],b=f[b][i];
        }
    }
    ans=min(ans,min(minn[a][0],minn[b][0]));
    return ans;
}
signed main(){
    cin>>n>>q;
    aa[0]=INT_MAX;
    for(int i=1;i<=n;i++){
        cin>>aa[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    for(int j=1;j<=22;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
            minn[i][j]=min(minn[i][j-1],minn[f[i][j-1]][j-1]);
        }
    }
    
    while(q--){
        int a,b;
        cin>>a>>b;
        cout<<lca(a,b)<<endl;
    }
    return 0;
}