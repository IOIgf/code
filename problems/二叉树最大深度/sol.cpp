/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-17 08:33:16 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-17 08:49:21
 */
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>g[100005];
int f[100005];
bool cmp(int x,int y){
    return x>y;
}
void dfs(int s){
    if(g[s].size()==0){
        f[s]=1;
        return;
    }
    int maxn=0;
    for(auto v:g[s]){
        dfs(v);
        maxn=max(maxn,f[v]);
    }
    f[s]=g[s].size()+maxn;
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
    }
    dfs(1);
    cout<<f[1];
    return 0;
}