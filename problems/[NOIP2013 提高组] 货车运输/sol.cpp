#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
struct node{
    int x,y,w;
}e[100005];
int fa[10005];
int cnt;
int f[10005][30],minn[10005][30];
int deep[10005];
vector<pair<int,int>>g[10005];
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void add(int x,int y){
    if(find(x)!=find(y)){
        fa[find(x)]=find(y);
    }
}
bool cmp(node x,node y){
    return x.w>y.w;
}
void dfs(int u,int faa){
    f[u][0]=faa;
    deep[u]=deep[faa]+1;
    for(auto [v,w]:g[u]){
        if(v==faa){
            continue;
        }
        minn[v][0]=w;
        dfs(v,u);
    }
}
int lca(int a,int b){
    int ans=INT_MAX;
    if(deep[a]<deep[b])swap(a,b);
    for(int i=22;i>=0;i--){
        if(deep[f[a][i]]>=deep[b]){
            ans=min(ans,minn[a][i]);
            a=f[a][i];
        }
    }
    if(a==b)return ans;
    for(int i=22;i>=0;i--){
        if(f[a][i]!=f[b][i]){
            ans=min(ans,min(minn[a][i],minn[b][i]));
            a=f[a][i],b=f[b][i];
        }
    }
    ans=min(ans,min(minn[a][0],minn[b][0]));
    return ans;
}
int q;
signed main(){
    cin>>n>>m;
    memset(minn,0x3f,sizeof(minn));
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>e[i].x>>e[i].y>>e[i].w;
    }
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=m;i++){
        if(find(e[i].x)!=find(e[i].y)){
            add(e[i].x,e[i].y);
            g[e[i].x].push_back({e[i].y,e[i].w});
            g[e[i].y].push_back({e[i].x,e[i].w});
            ++cnt;
        }
        if(cnt==n-1)break;
    }
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            dfs(i,0);
        }
    }
    for(int j=1;j<=22;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
            minn[i][j]=min(minn[i][j-1],minn[f[i][j-1]][j-1]);
        }
    }
    cin>>q;
    while(q--){
        int a,b;
        cin>>a>>b;
        if(find(a)!=find(b)){
            cout<<-1<<endl;
            continue;
        }
        cout<<lca(a,b)<<endl;
    }
    return 0;
}